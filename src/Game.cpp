//
// Created by oporu on 2024/1/25.
//
#include "../include/Game.hpp"
#include "../include/EntityUpdateParams.hpp"

Game::Game() :
		window(sf::VideoMode(800, 600), "idk", sf::Style::Close),
		tillSpawnEnemy(5000),
		status(STARTED),
		deadMessage(font),
		pausedMessage(font) {
	font.loadFromFile("font.ttf");
	sf::Image icon;
	if (icon.loadFromFile("icon.png"))
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	this->window.setFramerateLimit(60);
	this->window.setVerticalSyncEnabled(true);
	this->window.setActive(true);
}

bool Game::isActive() const {
	return window.isOpen();
}

void Game::update() {
	const sf::Int32 dt = clock.restart().asMilliseconds();
	this->handleWindowEvents();
	EntityUpdateParams params{dt, player, enemies, animations, animationsUnderPlayer, randomGen};
	healthDisplay.update(player);
	if (status == PAUSED) return;
	while (animations.size() > 1000)
		animations.erase(animations.begin(), animations.begin() + (long) (animations.size() - 1000));
	while (animationsUnderPlayer.size() > 1000)
		animationsUnderPlayer.erase(animationsUnderPlayer.begin() + (long) (animationsUnderPlayer.size() - 1000));
	for (auto it = animations.begin(); it != animations.end();) {
		if ((*it)->update(dt)) animations.erase(it);
		else it++;
	}
	for (auto it = animationsUnderPlayer.begin(); it != animationsUnderPlayer.end();) {
		if ((*it)->update(dt)) animationsUnderPlayer.erase(it);
		else it++;
	}
	if (status == DEAD) return;
	for (auto it = enemies.begin(); it != enemies.end();) {
		if ((*it)->update(params)) enemies.erase(it);
		else it++;
	}
	tillSpawnEnemy -= dt;
	if (tillSpawnEnemy <= 0) {
		spawnEnemy();
		tillSpawnEnemy = 5000;
	}

	if (this->player.update(params)) status = DEAD;
}

void Game::render() {
	this->window.clear(sf::Color::Black);

	window.setView(sf::View{player.getPosition(), static_cast<sf::Vector2f>(window.getSize())});

	for (auto &enemy: enemies)
		enemy->render(window);
	for (auto &animation: animationsUnderPlayer)
		animation->render(this->window);
	this->player.render(window);
	for (auto &animation: animations)
		animation->render(this->window);
	this->healthDisplay.render(window);
	if (status == DEAD)
		deadMessage.render(window);
	else if (status == PAUSED)
		pausedMessage.render(window);
	this->window.display();
}

void Game::handleWindowEvents() {
	sf::Event event{};
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			this->window.close();
			return;
		}
		if (event.type == sf::Event::LostFocus) {
			if (status == STARTED) status = PAUSED;
			continue;
		}
		if (event.type == sf::Event::KeyPressed) {
			using sf::Keyboard;
			switch (event.key.code) {
				case Keyboard::Q:
					this->window.close();
					return;
				case Keyboard::BackSpace:
					this->animations.clear();
					this->animationsUnderPlayer.clear();
					break;
				case Keyboard::R:
					this->restart();
					break;
				case Keyboard::Escape:
					if (status == STARTED)
						status = PAUSED;
					else if (status == PAUSED)
						status = STARTED;
					break;
				case Keyboard::Enter:
					this->spawnEnemy();
					break;
				case Keyboard::Add:
					for (int i = 0; i < 100; i++)
						this->spawnEnemy();
					break;
				default:;
			}
			continue;
		}
	}
}

void Game::spawnEnemy() {
	const sf::Vector2f &mid = player.getPosition();
	std::uniform_real_distribution<float> dist(1, 1e10);
	std::uniform_real_distribution<float> distance(600, 1100);
	std::uniform_int_distribution<short> negative(0, 1);

	sf::Vector2f pos = {dist(randomGen), dist(randomGen)};
	if (negative(randomGen)) pos.x *= -1;
	if (negative(randomGen)) pos.y *= -1;
	pos /= std::sqrt((pos.x * pos.x) + (pos.y * pos.y));
	pos *= distance(randomGen);
	pos += mid;
	enemies.push_back(std::make_shared<Enemy>(pos));
}

void Game::restart() {
	player = Player();
	tillSpawnEnemy = 5000;
	status = STARTED;
	enemies.clear();
	animations.clear();
	animationsUnderPlayer.clear();
}

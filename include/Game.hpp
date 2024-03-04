#include <SFML/Graphics.hpp>
#include <random>
#include "Player.hpp"
#include "Animation/Particle.hpp"
#include "Animation.hpp"
#include "Enemy.hpp"
#include "HealthDisplay.hpp"
#include "DeadMessage.hpp"
#include "PausedMessage.hpp"
#include <iostream>

class Enemy;

class HealthDisplay;

class DeadMessage;

class Game final {
public:
	enum class Status {
		STARTED, DEAD, PAUSED
	};

	Game();

	bool isActive() const;

	void update();

	void render();

	void restart();

private:
//	std::random_device randomDevice;
	std::mt19937 randomGen{std::random_device()()};
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Font font;
	sf::Int32 tillSpawnEnemy;
	std::vector<std::unique_ptr<Animation::Animation>> animations;
	std::vector<std::unique_ptr<Animation::Animation>> animationsUnderPlayer;
	std::vector<std::shared_ptr<Enemy>> enemies;
	Player player;
	HealthDisplay healthDisplay;
	Status status;
	DeadMessage deadMessage;
	PausedMessage pausedMessage;
	std::array<bool, sf::Keyboard::KeyCount> keyPressed {false};

	void handleWindowEvents();

	void spawnEnemy();
};


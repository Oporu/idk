//
// Created by oporu on 2024/1/25.
//
#include <iostream>
#include "../include/Player.hpp"
#include "../include/EntityUpdateParams.hpp"
#include "../include/Animation/Explosion.hpp"
#include "../include/Animation/FadingOutParticle.hpp"
#include "../include/Animation/Particle.hpp"

Player::Player() : maxHealth(10000), health(10000), coolDownToExplode(0), kills(0) {
	this->shape.setPosition(0, 0);
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(SIZE / 2.f);
}

void Player::explode(EntityUpdateParams &params) {
	if (coolDownToExplode > 0) return;
	coolDownToExplode = 1000;
	params.animations.push_back(std::make_unique<Animation::Explosion>(this->shape.getPosition()));
	LivingEntityTakeDamageParams p = {50, params.player, params.enemies, params.animations,
	                                  params.animationsUnderPlayer, params.randomGen};

	const sf::Vector2f &pos = this->shape.getPosition();
	for (std::shared_ptr<Enemy> &e: params.enemies) {
		using std::max, std::min;
		const sf::FloatRect bound = e->getGlobalBounds();
		const sf::Vector2f d = pos - sf::Vector2f{
				max(min(bound.left + bound.width, pos.x), bound.left),
				max(min(bound.top + bound.height, pos.y), bound.top)
		};
//		const sf::Vector2f d = pos - nearest;
		const float distanceSquared = (d.x * d.x) + (d.y * d.y);
		if (distanceSquared > 170 * 170) continue;
		if (e->takeDamage(p)) kills++;
	}
}

const sf::Vector2f &Player::getPosition() const {
	return shape.getPosition();
}

void Player::spawnTrails(std::vector<std::unique_ptr<Animation::Animation>> &animations) {
	const sf::FloatRect bound = this->shape.getGlobalBounds();
	sf::Vector2f pos[4] = {
			{bound.left + (Animation::FadingOutParticle::SIZE.x / 2),
					                                                                bound.top +
					                                                                (Animation::FadingOutParticle::SIZE.y /
					                                                                 2)},
			{bound.left + (Animation::FadingOutParticle::SIZE.x / 2),               bound.top -
			                                                                        (Animation::FadingOutParticle::SIZE.y /
			                                                                         2) + bound.height},
			{bound.left - (Animation::FadingOutParticle::SIZE.x / 2) + bound.width, bound.top +
			                                                                        (Animation::FadingOutParticle::SIZE.y /
			                                                                         2)},
			{bound.left - (Animation::FadingOutParticle::SIZE.x / 2) + bound.width, bound.top -
			                                                                        (Animation::FadingOutParticle::SIZE.y /
			                                                                         2) + bound.height}
	};
	for (const auto &item: pos)
		animations.push_back(
				std::make_unique<Animation::FadingOutParticle>(item, sf::Vector2f(0, 0), sf::Vector2f(0, 0),
				                                               sf::Color::White, 200));
}

bool Player::dead() const {
	return health <= 0;
}

bool Player::takeDamage(LivingEntityTakeDamageParams &params) {
	if (this->dead()) return true;
	health -= params.damage;

	// spawn blood particle
	{
		std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
		const sf::Vector2f pos = shape.getPosition() + sf::Vector2f{shape.getSize().x * dist(params.randomGen),
		                                                            shape.getSize().y * dist(params.randomGen)};

		const sf::Vector2f velocity = sf::Vector2f{dist(params.randomGen), dist(params.randomGen)} / 2.5f;
		const sf::Vector2f acceleration = sf::Vector2f{dist(params.randomGen), dist(params.randomGen)} / 5.f;
		params.animations.emplace_back(std::make_unique<Animation::Particle>(pos, velocity, acceleration));
	}

	if (this->dead()) {
		this->shape.setFillColor(sf::Color::Blue);
		return true;
	}
	return false;
}

bool Player::update(EntityUpdateParams &params) {
	coolDownToExplode -= params.dt;
	coolDownToExplode = std::max(coolDownToExplode, 0);
	if (params.keyPressed[sf::Keyboard::Space]) this->explode(params);
	sf::Vector2f move{0, 0};
	{
		using sf::Keyboard;
		move.y = -static_cast<float>(params.keyPressed[Keyboard::W]) -
		         static_cast<float>(params.keyPressed[Keyboard::Up]);
		move.x = -static_cast<float>(params.keyPressed[Keyboard::A]) -
		         static_cast<float>(params.keyPressed[Keyboard::Left]);
		move.y += static_cast<float>(params.keyPressed[Keyboard::S]) +
		          static_cast<float>(params.keyPressed[Keyboard::Down]);
		move.x += static_cast<float>(params.keyPressed[Keyboard::D]) +
		          static_cast<float>(params.keyPressed[Keyboard::Right]);
	}
	if (move != sf::Vector2f{0, 0}) {
		move /= std::sqrt(move.x * move.x + move.y * move.y);
		move *= static_cast<float>(params.dt) / 2;
		spawnTrails(params.animationsUnderPlayer);
	}
	shape.move(move);
	return this->dead();
}

sf::FloatRect Player::getGlobalBounds() const {
	return shape.getGlobalBounds();
}

sf::Int32 Player::getMaxHealth() const {
	return maxHealth;
}

sf::Int32 Player::getHealth() const {
	return health;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(this->shape, states);
}

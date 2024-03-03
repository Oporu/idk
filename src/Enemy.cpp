//
// Created by oporu on 2024/1/25.
//
#include "../include/Enemy.hpp"
#include "../include/EntityUpdateParams.hpp"
#include "../include/Animation/Particle.hpp"
#include <cmath>

Enemy::Enemy(const sf::Vector2f &position) {
	this->shape.setOrigin(SIZE / 2.0f);
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setPosition(position);
}

void Enemy::render(sf::RenderWindow &window) {
	window.draw(this->shape);
}

sf::FloatRect Enemy::getGlobalBounds() const {
	return this->shape.getGlobalBounds();
}

bool Enemy::takeDamage(LivingEntityTakeDamageParams &params) {
	health -= params.damage;
	return health >= 0;
}

bool Enemy::dead() const {
	return health >= 0;
}

const sf::Vector2f &Enemy::getPosition() const {
	return this->shape.getPosition();
}

bool Enemy::update(EntityUpdateParams &params) {
	sf::Vector2f move = params.player.getPosition() - this->shape.getPosition();
	if (move != sf::Vector2f{0, 0}) {
		move /= std::sqrt((move.x * move.x) + (move.y * move.y));
		move *= speed * (float) params.dt;
		this->shape.move(move);
	}

	if (this->getGlobalBounds().intersects(params.player.getGlobalBounds())) {
		LivingEntityTakeDamageParams p{params.dt, params.player, params.enemies, params.animations,
		                               params.animationsUnderPlayer, params.randomGen};
		params.player.takeDamage(p);
	}
	if (health <= 0) {
		sf::Vector2f velocity = this->shape.getPosition() - params.player.getPosition();
		if (velocity != sf::Vector2f{0, 0})
			velocity /= std::sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
		velocity *= speed * 3;
		params.animationsUnderPlayer.push_back(std::make_unique<DeathAnimation>(shape, velocity));
	}
	return health <= 0;
}

bool Enemy::DeathAnimation::update(sf::Int32 dt) {
	life -= dt;
	if (life <= 0) return true;
	shape.move(velocity * (float)dt);
	shape.setRotation((float)(life%360));
	return false;
}

void Enemy::DeathAnimation::render(sf::RenderWindow &window) {
	window.draw(shape);
}

Enemy::DeathAnimation::DeathAnimation(sf::RectangleShape shape, const sf::Vector2f& velocity, int life) : shape(std::move(shape)), velocity(velocity), life(life) {

}

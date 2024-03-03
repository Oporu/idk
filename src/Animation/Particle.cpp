//
// Created by oporu on 2024/1/25.
//

#include "../../include/Animation/Particle.hpp"

namespace Animation {
	Particle::Particle(const sf::Vector2f &position, const sf::Vector2f &velocity, const sf::Vector2f &acceleration,
	                   const sf::Color color, const sf::Int32 life) : velocity(velocity), acceleration(acceleration),
	                                                                  life(life) {
		this->shape.setPosition(position);
		this->shape.setOrigin(ORIGIN);
		this->shape.setFillColor(color);
	}

	// return true if particle is dead
	bool Particle::update(const sf::Int32 dt) {
		this->life -= dt;
		if (this->life <= 0) {
			return true;
		}

		this->velocity += this->acceleration * (float) dt;
		this->shape.move(this->velocity);
		return false;
	}

	void Particle::render(sf::RenderWindow &window) {
		window.draw(this->shape);
	}
}
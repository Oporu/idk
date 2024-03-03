//
// Created by oporu on 2024/1/25.
//

#include "../../include/Animation/Explosion.hpp"

namespace Animation {
	Explosion::Explosion(const sf::Vector2f &position) {
		shape.setPosition(position);
		shape.setOrigin(50, 50);
		const sf::Color color = sf::Color(100, 100, 100, 255);
		shape.setFillColor(color);
		shape.setOutlineColor(color);
	}

	bool Explosion::update(const sf::Int32 dt) {
		age += dt;
		if (age > 200) return true;
		shape.setOutlineThickness((float) age / 2);
		const sf::Color color = sf::Color(100, 100, 100, 255 - age);
		shape.setFillColor(color);
		shape.setOutlineColor(color);
		return false;
	}

	void Explosion::render(sf::RenderWindow &window) {
		window.draw(this->shape);
	}
}
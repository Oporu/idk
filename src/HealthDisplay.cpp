//
// Created by oporu on 2024/1/26.
//

#include "../include/HealthDisplay.hpp"
#include "../include/Player.hpp"
#include <SFML/Audio.hpp>

HealthDisplay::HealthDisplay() : empty(SIZE), filled(SIZE), previousFilled({0, 0}), previousPercentage(0) {
	empty.setFillColor(sf::Color(80, 80, 80));
	empty.setOutlineColor(sf::Color(100, 100, 100));
	empty.setOutlineThickness(3);

	filled.setFillColor(sf::Color::Red);
	filled.setSize({0, filled.getSize().y});
	previousFilled.setFillColor(sf::Color::White);
}

void HealthDisplay::update(const Player &player) {
	const float currentPercentage = ((float) player.getHealth() / (float) player.getMaxHealth());
	const float c = (previousPercentage * 29 + currentPercentage) / 30;
	filled.setSize({SIZE.x * currentPercentage, filled.getSize().y});
	previousFilled.setSize({SIZE.x * c, filled.getSize().y});
	previousPercentage = c;
}

void HealthDisplay::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	const sf::View &windowView = target.getView();
	const sf::Vector2f pos = windowView.getCenter() - (windowView.getSize() / 2.f);
	empty.setPosition(pos);
	filled.setPosition(pos);
	previousFilled.setPosition(pos);

	target.draw(empty, states);
	target.draw(previousFilled, states);
	target.draw(filled, states);
}

//
// Created by oporu on 2024/1/30.
//

#include "../include/DeadMessage.hpp"

DeadMessage::DeadMessage(const sf::Font &font)
		: text("\tYOU DIED\n PRESS R TO RESTART", font) {
	text.setFillColor(sf::Color::Red);
	text.setScale(2, 2);
}

void DeadMessage::render(sf::RenderWindow &window) {
	const sf::FloatRect bounds = text.getLocalBounds();;
	text.setOrigin(bounds.width / 2, bounds.height / 2);
	text.setPosition(window.getView().getCenter());
	window.draw(text);
}

void DeadMessage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	const sf::FloatRect bounds = text.getLocalBounds();
	this->text.setOrigin(bounds.width / 2, bounds.height / 2);
	this->text.setPosition(target.getView().getCenter());
	target.draw(text, states);
}

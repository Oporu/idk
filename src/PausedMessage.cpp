//
// Created by oporu on 2024/1/30.
//

#include "../include/PausedMessage.hpp"

PausedMessage::PausedMessage(const sf::Font &font) : text("\tPAUSED\n PRESS ESC TO CONTINUE", font) {
	text.setScale(2, 2);
	background.setFillColor(sf::Color(0, 0, 0, 60));
}

void PausedMessage::render(sf::RenderWindow &window) {
	background.setSize(static_cast<sf::Vector2f>(window.getSize()));
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(window.getView().getCenter());
	window.draw(background);
	const sf::FloatRect bounds = text.getLocalBounds();;
	text.setOrigin(bounds.width / 2, bounds.height / 2);
	text.setPosition(window.getView().getCenter());
	window.draw(text);
}
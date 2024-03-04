//
// Created by oporu on 2024/1/30.
//

#include "../include/PausedMessage.hpp"

PausedMessage::PausedMessage(const sf::Font &font) : text("\tPAUSED\n PRESS ESC TO CONTINUE", font) {
	text.setScale(2, 2);
	background.setFillColor(sf::Color(0, 0, 0, 60));
}

void PausedMessage::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	background.setSize(static_cast<sf::Vector2f>(target.getSize()));
	background.setOrigin(background.getSize() / 2.f);
	background.setPosition(target.getView().getCenter());
	target.draw(background, states);
	const sf::FloatRect bounds = text.getLocalBounds();;
	text.setOrigin(bounds.width / 2, bounds.height / 2);
	text.setPosition(target.getView().getCenter());
	target.draw(text, states);
}

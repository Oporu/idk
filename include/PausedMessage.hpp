//
// Created by oporu on 2024/1/30.
//

#ifndef IDK_PAUSEDMESSAGE_HPP
#define IDK_PAUSEDMESSAGE_HPP

#include <SFML/Graphics.hpp>

class PausedMessage final {
	sf::Text text;
	sf::RectangleShape background;

public:
	explicit PausedMessage(const sf::Font &font);

	void render(sf::RenderWindow &window);
};

#endif //IDK_PAUSEDMESSAGE_HPP

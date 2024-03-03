//
// Created by oporu on 2024/1/30.
//

#ifndef IDK_DEADMESSAGE_HPP
#define IDK_DEADMESSAGE_HPP

#include <SFML/Graphics.hpp>

class DeadMessage final {
	sf::Text text;
public:
	explicit DeadMessage(const sf::Font &font);

	void render(sf::RenderWindow &window);

};

#endif //IDK_DEADMESSAGE_HPP

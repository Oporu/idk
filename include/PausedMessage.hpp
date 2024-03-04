//
// Created by oporu on 2024/1/30.
//

#ifndef IDK_PAUSEDMESSAGE_HPP
#define IDK_PAUSEDMESSAGE_HPP

#include <SFML/Graphics.hpp>

class PausedMessage final : public sf::Drawable {
	mutable sf::Text text;
	mutable sf::RectangleShape background;

public:
	explicit PausedMessage(const sf::Font &font);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //IDK_PAUSEDMESSAGE_HPP

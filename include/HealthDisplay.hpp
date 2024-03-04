//
// Created by oporu on 2024/1/26.
//

#ifndef IDK_HEALTHDISPLAY_HPP
#define IDK_HEALTHDISPLAY_HPP

#include <SFML/Graphics.hpp>

class Player;

class HealthDisplay final : public sf::Drawable {
public:
	HealthDisplay();

	void update(const Player &player);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	static const inline sf::Vector2f SIZE{400, 30};
	mutable sf::RectangleShape empty;
	mutable sf::RectangleShape filled;
	mutable sf::RectangleShape previousFilled;
	float previousPercentage;
};

#endif //IDK_HEALTHDISPLAY_HPP

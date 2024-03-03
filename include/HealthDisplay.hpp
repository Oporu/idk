//
// Created by oporu on 2024/1/26.
//

#ifndef IDK_HEALTHDISPLAY_HPP
#define IDK_HEALTHDISPLAY_HPP

#include <SFML/Graphics.hpp>

class Player;

class HealthDisplay final {
public:
	HealthDisplay();

	void update(const Player &player);

	void render(sf::RenderWindow &window);

private:
	static const inline sf::Vector2f SIZE{400, 30};
	sf::RectangleShape empty;
	sf::RectangleShape filled;
	sf::RectangleShape previousFilled;
	float previousPercentage;
};

#endif //IDK_HEALTHDISPLAY_HPP

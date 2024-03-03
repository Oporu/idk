//
// Created by oporu on 2024/1/23.
//

#ifndef IDK_ENTITY_HPP
#define IDK_ENTITY_HPP

#include <SFML/Graphics.hpp>

struct EntityUpdateParams;

class Entity {
public:
	virtual bool update(EntityUpdateParams &params) = 0;

	virtual void render(sf::RenderWindow &window) = 0;

	[[nodiscard]] virtual sf::FloatRect getGlobalBounds() const = 0;

	[[nodiscard]] virtual const sf::Vector2f &getPosition() const = 0;
};


#endif //IDK_ENTITY_HPP

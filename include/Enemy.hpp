//
// Created by oporu on 2024/1/22.
//

#ifndef IDK_ENEMY_HPP
#define IDK_ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "LivingEntity.hpp"

class Enemy final : public LivingEntity {
	class DeathAnimation final : public Animation::Animation {
	public:
		bool update(sf::Int32 dt) override;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		DeathAnimation(sf::RectangleShape shape, const sf::Vector2f &velocity, int life = 2000);

	private:
		sf::RectangleShape shape;
		sf::Vector2f velocity;
		int life;
	};

	inline static const sf::Vector2f SIZE{50, 50};
	inline static const float speed = 1.f / 4;
	sf::RectangleShape shape{SIZE};
	int health{100};
public:
	explicit Enemy(const sf::Vector2f &position);

	bool update(EntityUpdateParams &params) override;

	bool takeDamage(LivingEntityTakeDamageParams &params) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::FloatRect getGlobalBounds() const override;

	bool dead() const override;

	const sf::Vector2f &getPosition() const override;
};


#endif //IDK_ENEMY_HPP

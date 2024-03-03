#ifndef IDK_PLAYER_HPP
#define IDK_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <complex>
#include "LivingEntity.hpp"

//#include "Enemy.hpp"
class Enemy;

struct EntityUpdateParams;

class Player final : public LivingEntity {
	inline static const sf::Vector2f SIZE{50, 50};
	sf::RectangleShape shape{SIZE};
	int maxHealth;
	int health;
	int coolDownToExplode;
	int kills;


	void spawnTrails(std::vector<std::unique_ptr<Animation::Animation>> &animations);

public:
	Player();

	bool update(EntityUpdateParams &params) override;

	void render(sf::RenderWindow &window) override;

	void explode(EntityUpdateParams &params);

	const sf::Vector2f &getPosition() const override;

	bool dead() const override;

	bool takeDamage(LivingEntityTakeDamageParams &params) override;

	sf::FloatRect getGlobalBounds() const override;

	sf::Int32 getHealth() const;

	sf::Int32 getMaxHealth() const;
};

#endif // IDK_PLAYER_HPP
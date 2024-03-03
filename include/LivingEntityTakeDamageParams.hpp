//
// Created by oporu on 2024/1/25.
//

#ifndef IDK_ENTITYTAKEDAMAGEPARAMS_HPP
#define IDK_ENTITYTAKEDAMAGEPARAMS_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
//#include "Player.hpp"
//#include "Enemy.hpp"
#include "Animation.hpp"

class Player;

class Enemy;

struct LivingEntityTakeDamageParams {
	const sf::Int32 damage;
	Player &player;
	std::vector<std::shared_ptr<Enemy>> &enemies;
	std::vector<std::unique_ptr<Animation::Animation>> &animations;
	std::vector<std::unique_ptr<Animation::Animation>> &animationsUnderPlayer;
	std::mt19937 &randomGen;
};

#endif //IDK_ENTITYTAKEDAMAGEPARAMS_HPP

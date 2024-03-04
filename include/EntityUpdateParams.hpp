//
// Created by oporu on 2024/1/25.
//

#ifndef IDK_ENTITYUPDATEPARAMS_HPP
#define IDK_ENTITYUPDATEPARAMS_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Animation.hpp"

class Player;

class Enemy;
namespace Animation {
	class Animation;
}
struct EntityUpdateParams {
	const sf::Int32 dt;
	Player &player;
	std::vector<std::shared_ptr<Enemy>> &enemies;
	std::vector<std::unique_ptr<Animation::Animation>> &animations;
	std::vector<std::unique_ptr<Animation::Animation>> &animationsUnderPlayer;
	std::mt19937 &randomGen;
	const std::array<bool, sf::Keyboard::KeyCount> &keyPressed;
};

#endif //IDK_ENTITYUPDATEPARAMS_HPP

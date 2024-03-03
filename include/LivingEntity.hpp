//
// Created by oporu on 2024/1/23.
//

#ifndef IDK_LIVINGENTITY_HPP
#define IDK_LIVINGENTITY_HPP

#include "Entity.hpp"
#include "LivingEntityTakeDamageParams.hpp"

class LivingEntity : public Entity {
public:
	virtual bool dead() const = 0;

	virtual bool takeDamage(LivingEntityTakeDamageParams &params) = 0;
};


#endif //IDK_LIVINGENTITY_HPP

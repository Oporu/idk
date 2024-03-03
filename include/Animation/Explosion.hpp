//
// Created by oporu on 2024/1/20.
//

#ifndef IDK_EXPLOSION_HPP
#define IDK_EXPLOSION_HPP

#include "../Animation.hpp"

namespace Animation {
	class Explosion final : public Animation {
		int age{0};
		sf::CircleShape shape{50};
	public:
		explicit Explosion(const sf::Vector2f &position);

		bool update(sf::Int32 dt) override;

		void render(sf::RenderWindow &window) override;
	};
}


#endif //IDK_EXPLOSION_HPP

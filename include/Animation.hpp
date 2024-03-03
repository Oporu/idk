//
// Created by oporu on 2024/1/20.
//

#ifndef IDK_ANIMATION_HPP
#define IDK_ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace Animation {
	class Animation {
	public:
		virtual ~Animation() = default;

		virtual bool update(sf::Int32 dt) = 0;

		virtual void render(sf::RenderWindow &window) = 0;
	};
}


#endif //IDK_ANIMATION_HPP

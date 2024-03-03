#ifndef IDK_PARTICLE_HPP
#define IDK_PARTICLE_HPP

#include <SFML/Graphics.hpp>
#include "../Animation.hpp"

namespace Animation {
	class Particle final : public Animation {
		sf::Int32 life;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::RectangleShape shape{SIZE};
	public:
		inline static const sf::Vector2f SIZE{10, 10};
		inline static const sf::Vector2f ORIGIN{SIZE / 2.0f};

		Particle(const sf::Vector2f &position, const sf::Vector2f &velocity, const sf::Vector2f &acceleration,
		         sf::Color color = sf::Color::Red, sf::Int32 life = 1000);

		bool update(sf::Int32 dt) override;

		void render(sf::RenderWindow &window) override;
	};


}
#endif
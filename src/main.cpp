#include "../include/Game.hpp"

int main() {
	Game game;
	while (game.isActive()) {
		game.update();
		game.render();
	}
}

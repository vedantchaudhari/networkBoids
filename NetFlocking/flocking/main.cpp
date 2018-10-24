#include "SDL.h"

#include "Define.h"
#include "Flock.h"
#include "SDLInterface.h"

#undef main

void update() {
	SDLInterface::getInstance()->render();
	SDLInterface::getInstance()->background();
	SDLInterface::getInstance()->setColor(255, 255, 255, 255);
}

void main() {
	SDLInterface::getInstance()->init(WIDTH, HEIGHT, TITLE);
	Flock flock = Flock(NUM_BOIDS);

	Uint32 iTime = SDL_GetTicks();
	Uint32 iTime2 = 0;

	while (1) {
		iTime2 = SDL_GetTicks();

		if (iTime2 - iTime >= TICK) {
			iTime = SDL_GetTicks();
			flock.update();
		}

		flock.render();
		update();
	}

	SDLInterface::getInstance()->exit();
}
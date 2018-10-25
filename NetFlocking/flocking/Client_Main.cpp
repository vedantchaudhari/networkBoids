#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <vector>

#include "Define.h"
#include "Flock.h"
#include "SDLInterface.h"
#include "InputInterface.h"

void update() {
	SDLInterface::getInstance()->render();
	SDLInterface::getInstance()->background();
	
	InputInterface::getInstance()->update();

	SDLInterface::getInstance()->setColor(255, 255, 255, 255);
}

int main(int argc, char *argv[]) {
	SDLInterface::getInstance()->init(WIDTH, HEIGHT, TITLE);
	Flock flock = Flock(NUM_BOIDS);

	Uint32 iTime = SDL_GetTicks();
	Uint32 iTime2 = 0;

	while (SDLInterface::getInstance()->isExit == false) {
		iTime2 = SDL_GetTicks();

		if (iTime2 - iTime >= TICK) {
			iTime = SDL_GetTicks();
			flock.update();
		}

		flock.render();
		update();
	}

	SDLInterface::getInstance()->exit();
	return 0;
}
#include "SDLInterface.h"

SDLInterface* SDLInterface::mInstance = NULL;

SDLInterface::SDLInterface() {
	this->mpWindow = NULL;
	this->mpRenderer = NULL;
}

SDLInterface::~SDLInterface() {
	SDL_DestroyRenderer(mpRenderer);
	SDL_DestroyWindow(mpWindow);
}

void SDLInterface::init(int width, int height, const std::string& title) {
	if (SDL_Init(SDL_INIT_VIDEO))
		return;

	mpWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		width, height, SDL_WINDOW_OPENGL);
	if (mpWindow == NULL)
		return;

	// Initialize PNG images
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		return;

	mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mpWindow == NULL)
		return;

	this->mWindowWidth = width;
	this->mWindowHeight = height;
}

void SDLInterface::render() {
	SDL_RenderPresent(mpRenderer);
}

void SDLInterface::exit() {
	SDL_Quit();
}
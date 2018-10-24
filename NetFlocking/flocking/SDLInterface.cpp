#include "SDL.h"
#include "SDL_image.h"

#include "SDLInterface.h"

SDLInterface* SDLInterface::mInstance = NULL;

SDLInterface::SDLInterface() {
	this->mpWindow = NULL;
	this->mpRenderer = NULL;
}

SDLInterface::~SDLInterface() {
}

SDLInterface* SDLInterface::getInstance() {
	if (mInstance = NULL)
		mInstance = new SDLInterface();

	return mInstance;
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
	SDL_DestroyRenderer(mpRenderer);
	SDL_DestroyWindow(mpWindow);
	SDL_Quit();
}

void SDLInterface::background() {
	setColor(0, 0, 0, 255);
	SDL_RenderClear(mpRenderer);
}

void SDLInterface::setColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(mpRenderer, r, g, b, a);
}

void SDLInterface::drawTriangle(float x, float y, float width, float height, float angle) {
	// Right Corner
	float x1 = width / 2;
	float y1 = 0;

	// Left Top
	float x2 = -width / 2;
	float y2 = -height / 2;

	// Left Bottom
	float x3 = -width / 2;
	float y3 = height / 2;

	float s = sin(-angle);
	float c = cos(-angle);

	float x1r = (x1 * c) - (y1 * s) + x;
	float y1r = (x1 * s) + (y1 * c) + y;

	float x2r = (x2 * c) - (y2 * s) + x;
	float y2r = (x2 * s) + (y2 * c) + y;

	float x3r = (x3 * c) - (y3 * s) + x;
	float y3r = (x3 * s) + (y3 * c) + y;

	SDL_RenderDrawLine(mpRenderer, x1r, y1r, x2r, y2r);
	SDL_RenderDrawLine(mpRenderer, x2r, y2r, x3r, y3r);
	SDL_RenderDrawLine(mpRenderer, x3r, y3r, x1r, y1r);
}
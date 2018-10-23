#pragma once

#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_image.h"

class SDLInterface {
private:
	static SDLInterface* mInstance;

	SDL_Window* mpWindow;
	SDL_Renderer* mpRenderer;

	int mWindowWidth;
	int mWindowHeight;

public:
	SDLInterface();
	~SDLInterface();

	void init(int width, int height, const std::string& name);
	void render();
	void exit();

	// Getters
	static SDLInterface* getInstance();

	inline SDL_Window* getWindow() { return mpWindow; };
	inline SDL_Renderer* getRenderer() { return mpRenderer; };

	inline int getWidth() { return mWindowWidth; };
	inline int getHeight() { return mWindowHeight; };
};
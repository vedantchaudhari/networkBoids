#include "InputInterface.h"

#include "SDL.h"

InputInterface* InputInterface::mpInstance = NULL;

InputInterface::InputInterface() {
	mNumKeys = NULL;
}

InputInterface* InputInterface::getInstance() {
	if (mpInstance == NULL)
		mpInstance = new InputInterface();

	return mpInstance;
}

void InputInterface::onKeyDown() {
	mpVKeyState = SDL_GetKeyboardState(&mNumKeys);
}

void InputInterface::onKeyUp() {
	mpVKeyState = SDL_GetKeyboardState(&mNumKeys);
}
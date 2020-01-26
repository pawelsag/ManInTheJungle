#ifndef EVENTMANAGER
#define EVENTMANAGER

#include <SDL2/SDL.h>
#include <thread>
#include <stdio.h>

#include "textureStateManager.h"

class gameController;

class eventManager
{
	friend class gameController;
	SDL_Event event;
	// move flags to manatin movement
	bool isKeyUpPressed, isLeftPressed,isRightPressed, iskeyDownPressed;
	// if error occured or program is about to leave, isAboutToExit = true
	bool isAboutToExit;
	// ptr to main class controlling object state
	textureStateManager *currentPlayerStatePtr;
	// service every incoming event in this thread
	std::thread eventManagerThread;

public:
	eventManager() = default;

	eventManager(textureStateManager & textureManager);
	~eventManager();
	void run();
	void makeMove(SDL_Keycode & keyID);
	void clearMove(SDL_Keycode & keyID);

};

#endif
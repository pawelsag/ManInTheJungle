#include <SDL2/SDL.h>
#include "levelLoader.h"
#ifndef OBJECTMANAGER
#define OBJECTMANAGER
// this class is responsible for loading, and preapring 
// all textures necessary for each level 
class objectManager
{
	friend class gameController;

private: // members
	// 
	std::vector<renderObject*> BackgroundObjects;
	std::vector<renderObject*> JungleObjects;
	SDL_Renderer & renderObject;

	// object load levels and store map for given level
	levelLoader levelManager;
	char_ptr levelMap;

public:
	objectManager(SDL_Renderer & renderObject);
	~objectManager();

private: // helper functions
	void loadBackground();
	void loadLevel();
	void loadMainCharacter(){};

	
};

#endif
#include <SDL2/SDL.h>
#ifndef OBJECTMANAGER
#define OBJECTMANAGER

class objectManager
{
	friend class gameController;

private: // members
	std::vector<renderObject*> GameObjects;
	SDL_Renderer & renderObject;
public:
	objectManager(SDL_Renderer & renderObject);
	~objectManager(){};

private: // helper functions
	void loadBackground();
	void loadJungle(){};
	void loadMainCharacter(){};
	
};

#endif
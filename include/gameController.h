#include <vector>
#include <SDL2/SDL.h>
#include "BackgroundObject.h"
#include "rednerMachine.h"
#include "globalSettings.h"
#include <windows.h>
#include "customTypes.h"
#include "objectManager.h"
#ifndef GAMECONTROLLER
#define GAMECONTROLLER

struct Point{
	int x,y;
};
 
// this class use global settings to load levels and texture from files,
class gameController
{
private://members
	// main class which keep all loaded objects
	objectManager *objectsManager;
	// main class to render prepared configuration on screen
	rednerMachine display;
	// variabel holds currently invoked event  
	SDL_Event event;
	STATES globalState;
	// variabels keep info about currently set speed
	double velocityHorizontal{ 0.0 };
	double velocityVertical{ 0.0 };
	// main values, that follow main camera position
	int absoluteValueX{0};
	int absoluteValueY{0};
	// we need 1 extra column rendered bacause when we have to fill the gap on the edge of screen
	size_t mapColCount = ((SCREEN_WIDTH/JUNGLE_TILE_X_SIZE)+1);
	size_t mapRowCount = (SCREEN_HEIGHT/JUNGLE_TILE_Y_SIZE);
	size_t jungleItemsCount = mapColCount * mapRowCount;
	size_t currentRenderOffset_x;
	size_t currentRenderOffset_y, currentRenderOffset_y_copy; 

public:
	gameController();
	void run();
	~gameController();
private: // methods
	void loadTextures();
	void validateMove();
	void makeMove( SDL_Keycode & keyID );
	void clearMove( SDL_Keycode & keyID );
	void updateObjectsPosition();


};

#endif
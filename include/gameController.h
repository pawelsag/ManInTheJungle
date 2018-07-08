#include <vector>
#include <SDL2/SDL.h>
#include "BackgroundObject.h"
#include "rednerMachine.h"
#include "globalSettings.h"
#include <windows.h>
#include "customTypes.h"
#include "objectManager.h"
#include <characterObject.h>
#ifndef GAMECONTROLLER
#define GAMECONTROLLER
constexpr const int POSTIVE_VELOCITY = 5;
constexpr const int NEGATIVE_VELOCITY = -5;

struct Point{
	int x,y;
};
 
// this class use global settings to load levels and texture from files,
class gameController
{
	// movemnt statets 
	enum MOVE{
		IDLE =0,
		MOVE_X_VALID=1,
		MOVE_Y_VALID=2,
		MOVE_X_INVALID=4,
		MOVE_Y_INVALID=8

	};
	inline friend MOVE operator |(MOVE a, MOVE b)
	{
	    return static_cast<MOVE>(static_cast<int>(a) | static_cast<int>(b));
	}
	inline friend MOVE& operator |=(MOVE& a, MOVE b)
	{
		return a= a | b;
	}

private://members
	// main class which keep all loaded objects
	objectManager *objectsManager;
	// main class to render prepared configuration on screen
	rednerMachine display;
	// variabel holds currently invoked event  
	SDL_Event event;
	STATES globalState;
	// variabels keep info about currently set speed
	int velocityHorizontal{ 0 };
	int velocityVertical{ 0 };
	// main values, that follow main camera position
	int absolutePositionX{0};
	int absolutePositionY{0};
	// variables holds information about tiles render position
	int jungleTilePosition_x{0}, jungleTilePosition_y{0};
	// we need 1 extra column rendered bacause when we have to fill the gap on the edge of screen
	size_t mapColCount = ((SCREEN_WIDTH/JUNGLE_TILE_X_SIZE)+1);
	size_t mapRowCount = (SCREEN_HEIGHT/JUNGLE_TILE_Y_SIZE);
	size_t jungleItemsCount = mapColCount * mapRowCount;
	size_t currentRenderOffset_x;
	size_t currentRenderOffset_y, currentRenderOffset_y_copy; 
	// variable to validate move
	MOVE isMoveValid{MOVE::IDLE};
	ST::CHARACTERSTATE currentPlayerState{ST::CHARACTERSTATE::IDLE};
	// evry level starts on platform consist of 3 block of ground and 2 block of player = 5*JUNGLE_TILE_Y_SIZE
	int playerStartOffset_x{10}, playerStartOffset_y{SCREEN_HEIGHT - 5*JUNGLE_TILE_Y_SIZE }; 
public:
	gameController();
	void run();
	~gameController();
private: // methods
	void loadTextures();
	MOVE validateMove();
	void makeMove( SDL_Keycode & keyID );
	void clearMove( SDL_Keycode & keyID );
	void updateObjectsPosition();


};

#endif
#include <vector>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include <characterObject.h>
#include <gravitation.h>

#include "BackgroundObject.h"
#include "rednerMachine.h"
#include "globalSettings.h"
#include "customTypes.h"
#include "objectManager.h"
#include "textureStateManager.h"
#include "eventManager.h"

#ifndef GAMECONTROLLER
#define GAMECONTROLLER
constexpr const int POSTIVE_VELOCITY = 5;
constexpr const int NEGATIVE_VELOCITY = -5;
constexpr const int CAMERA_START_MOVE_X_OFFSET = 300;
constexpr const int CAMERA_START_MOVE_Y_OFFSET = 150;

constexpr const int CAMERA_START_X_OFFSET = 0;
constexpr const int CAMERA_START_Y_OFFSET = 200;

struct Point{
	int x,y;
};

// this class use global settings to load levels and texture from files,
class gameController
{
	// movement statets
	enum MOVE{
		IDLE =0,
		MOVE_X_VALID=1,
		MOVE_Y_VALID=2,
		MOVE_X_INVALID=4,
		MOVE_Y_INVALID=8,
		MOVE_Y_INVALID_IN_PROGRESS=16,
		MOVE_DOWN_INVALID =32,

	};
	inline friend MOVE operator |(MOVE a, MOVE b)
	{
	    return static_cast<MOVE>(static_cast<int>(a) | static_cast<int>(b));
	}
	inline friend MOVE operator &(MOVE a, MOVE b)
	{
		return static_cast<MOVE>(static_cast<int>(a) & static_cast<int>(b));
	}
	inline friend MOVE operator ~(MOVE a)
	{
		return static_cast<MOVE>(~static_cast<int>(a));
	}
	inline friend MOVE& operator |=(MOVE& a, MOVE b)
	{
		return a= a | b;
	}
	inline friend MOVE& operator &=(MOVE& a, MOVE b)
	{
		return a= a & b;
	}


private://members
	// main class which keep all loaded objects
	objectManager *objectsManager;
	// main class to render prepared configuration on screen
	rednerMachine display;
	// main class to manage gravitation
	gravitation gravityObject;
	// keep actual informations about curently vertical velocity
	gravitation::gravityDetails currentVerticalVelocity;
	// main class to manage currently used texture for player
	textureStateManager currentPlayerState;
	// main class to manage icomming events
	eventManager *event;
	// variabels keep info about currently set speed
	int velocityHorizontal{ 0 };
	int velocityVertical{ 0 };
	// main values, that follow main camera position
	int cameraPositionX{ CAMERA_START_X_OFFSET };
	int cameraPositionY{ CAMERA_START_Y_OFFSET };
	// hold copy of next player move
	int preX_Move{ 0 };
	int preY_Move{ 0 };
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
	// evry level starts on platform consist of 3 block of ground and 2 block of player = 5*JUNGLE_TILE_Y_SIZE
	int playerStartOffset_x{10}, playerStartOffset_y{SCREEN_HEIGHT - 5*JUNGLE_TILE_Y_SIZE };
	int playerX_Offset, playerY_Offset;
public:
	gameController();
	void run();
	~gameController();
private: // methods

	void updateObjectsPosition();

	MOVE validateMove();
	bool isPlayerInObstacle(MOVE &state);
	void checkMove( );

	// some function to validate move correctnes

	bool validateMoveLeft(MOVE &state);
	bool validateMoveRight(MOVE &state);
	bool validateMoveUp(MOVE &state);
	bool validateMoveDown(MOVE &state);

	// functions to callulates offsets before render
	void callculateXOfssets();
	void callculateYOfssets();
};

#endif
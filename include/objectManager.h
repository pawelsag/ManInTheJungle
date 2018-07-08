#include <SDL2/SDL.h>
#include "levelLoader.h"
#include "renderObject.h"
#include "jungleObject.h"
#include "characterObject.h"
#include <array>
#include "customTypes.h"
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
	std::vector<JungleTilesSettings> JungleTilesInfo;
	SDL_Renderer & renderObject;

	// object load levels and store map for given level
	levelLoader levelManager;
	PType::u_char_ptr mapLevel;

	// this is table which cointains the visible amount of tiles to render
	// during rendering change only the position of each tile and what to render
	std::unique_ptr<jungleObject[]> visibleRenderTiles;
	std::unique_ptr<characterObject[]> MainPlayerObjects;

	containerSize levelSize;
	// fast state lokok-up tabel
	// translate states to get object with proper texture 
	std::array<uint32_t, ST::STATE_COUNT > stateLookUpTable;
	// var with map size
	size_t mapRowsCount, mapColsCount;
public:
	objectManager(SDL_Renderer & renderObject, size_t x_size, size_t y_size);
	~objectManager();

	inline auto & getJungleTileInfo(unsigned char signature)const {
		
		for( auto & jungleTile : this->JungleTilesInfo)
		{
			if( jungleTile.code  == signature)
				return jungleTile;
		}
		return this->JungleTilesInfo[0];
	}


private: // helper functions
	void loadBackground();
	void loadLevel();
	void loadMainCharacter();

	
};

#endif
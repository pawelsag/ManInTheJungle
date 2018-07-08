#include "gameController.h"


objectManager::objectManager(SDL_Renderer & renderObject, size_t x_size, size_t y_size)
:renderObject(renderObject), 
visibleRenderTiles(new jungleObject[ ( x_size+1) * y_size ] ),
MainPlayerObjects(new characterObject[sizeof(ST::CHARACTERSTATE) ]),
 mapRowsCount(y_size), mapColsCount(x_size)
{
	printf("%i\n",sizeof(ST::CHARACTERSTATE) );
	this->loadBackground();
	this->loadMainCharacter();
	this->loadLevel();

}

void objectManager::loadBackground(){

	std::string fileName("plx-1.png");
	// load background
	for(int i =1 ; i < 6 ; i++){
		fileName[4] = (char)(i + 0x30);
		// make texture bit bigger than screen to simulate movment
		this->BackgroundObjects.push_back( new BackgroundObject(0, -200, SCREEN_WIDTH ,SCREEN_HEIGHT + 200 ) );
		this->BackgroundObjects[i-1]->loadTexturesFromFile((pathToBG + fileName) ,renderObject);
	}

	auto backgroundSize =BackgroundObjects.size();
	
	for(size_t i =0 ; i < backgroundSize; i++){
		// make copy of loaded texture
		this->BackgroundObjects.push_back(new BackgroundObject( this->BackgroundObjects[i] ) );
		// set new position
		this->BackgroundObjects[ i + backgroundSize ]->setPosition(SCREEN_WIDTH,-200);
		this->BackgroundObjects[ i + backgroundSize ]->setBeginPosition(SCREEN_WIDTH,-200);
		
	}
	printf("Loading file done\n");

}
void objectManager::loadLevel(){
	std::string fileName("jungle tileset.png");

	// all information about loaded signatures are in ./config/README.docx file
	levelManager.loadLevel( levels[0] );
	mapLevel = std::move(levelManager.getLevel());

	levelSize = levelManager.getLevelSize();
	auto & signatures = levelManager.getSignature();

	// tempoorary variable, just for preapred new jungle objects 
	SDL_Rect cropedTexture;
	// load texture to this object and share it with others objects
	jungleObject temporary_item( 0,0,JUNGLE_TILE_X_SIZE,JUNGLE_TILE_Y_SIZE,0 );
	temporary_item.loadTexturesFromFile((pathToJungleTiles + fileName) ,renderObject);
	// share texture with every visible tile
	for(size_t i =0 ; i < ( mapColsCount+1) * mapRowsCount ; i++ ){
		this->visibleRenderTiles[i] = temporary_item;

	}

	for(auto & sign : signatures){
		// contruct object with temp position, and size
		cropedTexture.w = 12;
		cropedTexture.h = 12;
		switch(sign){
			case 0x0:
			cropedTexture.x = 0;
			cropedTexture.y = 0;
			JungleTilesInfo.push_back( JungleTilesSettings( 0x0,cropedTexture ) );
			break;
			case 0x76:
			//light ground	
			cropedTexture.x = 30;
			cropedTexture.y = 30;
			JungleTilesInfo.push_back( JungleTilesSettings(0x76,cropedTexture) );

			break;
			case 0xEB:
			//dark ground
			cropedTexture.x = 30;
			cropedTexture.y = 42;
			JungleTilesInfo.push_back( JungleTilesSettings(0xEB,cropedTexture) );
			break;
			case 0x46:
			// lawn
			cropedTexture.x = 30;
			cropedTexture.y = 18;
			JungleTilesInfo.push_back( JungleTilesSettings(0x46,cropedTexture) );

			break;

		}
	}

}

void objectManager::loadMainCharacter(){
	std::vector<ST::CHARACTERSTATE_INFO> characterTextureState = 
	{
		ST::CHARACTERSTATE_INFO(charcterStateNames[0],ST::CHARACTERSTATE::IDLE),
		ST::CHARACTERSTATE_INFO(charcterStateNames[1],ST::CHARACTERSTATE::JUMP),
		ST::CHARACTERSTATE_INFO(charcterStateNames[2],ST::CHARACTERSTATE::RUNLEFT),
		ST::CHARACTERSTATE_INFO(charcterStateNames[3],ST::CHARACTERSTATE::RUNRIGHT),
		ST::CHARACTERSTATE_INFO(charcterStateNames[4],ST::CHARACTERSTATE::HANG),
		ST::CHARACTERSTATE_INFO(charcterStateNames[5],ST::CHARACTERSTATE::SPECIAL),
		ST::CHARACTERSTATE_INFO(charcterStateNames[6],ST::CHARACTERSTATE::LANDING),
	};
	int i =0;
	for(auto & st : characterTextureState){
		MainPlayerObjects[i] = characterObject(0,0,60,80,st.State) ;
		MainPlayerObjects[i].loadTexturesFromFile(st.TextureName,renderObject);
	}

}

objectManager::~objectManager(){
	for(auto & object : BackgroundObjects)
		delete object;
	
}
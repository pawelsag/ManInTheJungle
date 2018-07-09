#include "gameController.h"


objectManager::objectManager(SDL_Renderer & render_Object, size_t x_size, size_t y_size)
:render_Object(render_Object), 
visibleRenderTiles(new jungleObject[ ( x_size+1) * y_size ] ),
MainPlayerObjects(new characterObject[ ST::STATE_COUNT ]),
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
		this->BackgroundObjects[i-1]->loadTexturesFromFile((pathToBG + fileName) ,render_Object);
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
	temporary_item.loadTexturesFromFile((pathToJungleTiles + fileName) ,render_Object);
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
	// main charater object vector with given states
	std::vector<ST::CHARACTERSTATE_INFO> characterTextureState = 
	{
		ST::CHARACTERSTATE_INFO(charcterStateNames[0],ST::CHARACTERSTATE::IDLE,12,19,34),
		ST::CHARACTERSTATE_INFO(charcterStateNames[1],ST::CHARACTERSTATE::JUMP,1,17,34),
		ST::CHARACTERSTATE_INFO(charcterStateNames[2],ST::CHARACTERSTATE::RUNLEFT,8,21,33),
		ST::CHARACTERSTATE_INFO(charcterStateNames[3],ST::CHARACTERSTATE::RUNRIGHT,8,21,33),
		ST::CHARACTERSTATE_INFO(charcterStateNames[4],ST::CHARACTERSTATE::HANG,5,21,41),
		ST::CHARACTERSTATE_INFO(charcterStateNames[5],ST::CHARACTERSTATE::SPECIAL,2,20,35),
		ST::CHARACTERSTATE_INFO(charcterStateNames[6],ST::CHARACTERSTATE::LANDING,1,20,35),
	};
	// when above vecor change states, this LookUp table have to be updated
	stateLookUpTable[ST::CHARACTERSTATE::IDLE] = 0;
	stateLookUpTable[ST::CHARACTERSTATE::JUMP] = 1;
	stateLookUpTable[ST::CHARACTERSTATE::RUNLEFT] = 2;
	stateLookUpTable[ST::CHARACTERSTATE::RUNRIGHT] = 3;
	stateLookUpTable[ST::CHARACTERSTATE::HANG] = 4;
	stateLookUpTable[ST::CHARACTERSTATE::SPECIAL] = 5;
	stateLookUpTable[ST::CHARACTERSTATE::LANDING] = 6;

	int i =0;
	for(auto & st : characterTextureState){
		MainPlayerObjects[i] = characterObject(0,0,60,80,st.State) ;
		MainPlayerObjects[i].loadTexturesFromFile(std::string(pathToCharacter) + st.TextureName,render_Object);
		MainPlayerObjects[i].generateCropArea(st.n,st.w,st.h);
		i++;
	}

}

objectManager::~objectManager(){
	for(auto & object : BackgroundObjects)
		delete object;
	
}
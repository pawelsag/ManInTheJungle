#include "gameController.h"
#include "jungleObject.h"

objectManager::objectManager(SDL_Renderer & renderObject)
:renderObject(renderObject)
{
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
		this->BackgroundObjects.push_back( new BackgroundObject(0, 0, SCREEN_WIDTH ,SCREEN_HEIGHT + 100 ) );
		this->BackgroundObjects[i-1]->loadTexturesFromFile((pathToBG + fileName) ,renderObject);
	}

	auto backgroundSize =BackgroundObjects.size();
	
	for(size_t i =0 ; i < backgroundSize; i++){
		// make copy of loaded texture
		this->BackgroundObjects.push_back(new BackgroundObject( this->BackgroundObjects[i] ) );
		// set new position
		this->BackgroundObjects[ i + backgroundSize ]->setPosition(SCREEN_WIDTH,0);
		this->BackgroundObjects[ i + backgroundSize ]->setBeginPosition(SCREEN_WIDTH,0);
		
	}
	printf("Loading file done\n");

}
void objectManager::loadLevel(){
	std::string fileName("jungle tileset.png");

	// all information about loaded signatures are in ./config/README.docx file
	levelManager.loadLevel( levels[0] );
	levelMap = std::move(levelManager.getLevel());
	auto & signatures = levelManager.getSignature();

	// tempoorary variable, just for preapred new jungle objects 
	jungleObject *item;
	SDL_Rect cropedTexture;
	// load texture to this object and share it with others objects
	jungleObject temporary_item( 0,0,40,40,0 );
	temporary_item.loadTexturesFromFile((pathToJungleTiles + fileName) ,renderObject);
	for(auto & sign : signatures){
		// contruct object with temp position, and size
		cropedTexture.w = 12;
		cropedTexture.h = 12;
		
		switch(sign){
			case 0x0:
			// nothing
			break;
			case 0x76:
			//dark ground	
			cropedTexture.x = 30;
			cropedTexture.y = 42;
			item = new jungleObject( 0,0,40,40, 0x76);
			item->setTextutreMetaData(cropedTexture);
			item->setLoadedTexture(temporary_item);
			JungleObjects.push_back( item );

			break;
			case 0xEB:
			//light ground
			cropedTexture.x = 30;
			cropedTexture.y = 30;
			item = new jungleObject( 0,0,40,40, 0xEB);
			item->setTextutreMetaData(cropedTexture);
			item->setLoadedTexture(temporary_item);
			JungleObjects.push_back( item );
			break;
			case 0x46:
			// lawn
			cropedTexture.x = 30;
			cropedTexture.y = 18;
			item = new jungleObject( 0,0,40,40, 0x46);
			item->setTextutreMetaData(cropedTexture);
			item->setLoadedTexture(temporary_item);
			JungleObjects.push_back( item );
			break;

		}
	}	
}

objectManager::~objectManager(){
	for(auto & object : BackgroundObjects)
		delete object;
	
	for(auto & object : JungleObjects)
		delete object;

}
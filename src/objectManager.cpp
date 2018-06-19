#include "gameController.h"

objectManager::objectManager(SDL_Renderer & renderObject)
:renderObject(renderObject)
{
	this->loadBackground();
	this->loadMainCharacter();
	this->loadGround();
}
void objectManager::loadBackground(){

	std::string fileName("plx-1.png");
	// load background
	for(int i =1 ; i < 6 ; i++){
		fileName[4] = (char)(i + 0x30);
		// make texture bit bigger than screen to simulate movment
		this->GameObjects.push_back( new BackgroundObject(0, 0, SCREEN_WIDTH ,SCREEN_HEIGHT + 100 ) );
		this->GameObjects[i-1]->loadTexturesFromFile((pathToBG + fileName) ,renderObject);
	}
	auto backgroundSize =GameObjects.size();
	
	for(size_t i =0 ; i < backgroundSize; i++){
		// make copy of loaded texture
		this->GameObjects.push_back(new BackgroundObject( this->GameObjects[i] ) );
		// set new position
		this->GameObjects[ i + backgroundSize ]->setPosition(SCREEN_WIDTH,0);
		this->GameObjects[ i + backgroundSize ]->setBeginPosition(SCREEN_WIDTH,0);
		
	}
	printf("Loading file done\n");
}

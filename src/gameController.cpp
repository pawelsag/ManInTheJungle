#include "gameController.h"

gameController::gameController(){
	objectsManager = new objectManager( this->display.getRenderObject(), this->mapColCount, this->mapRowCount);
	currentRenderOffset_x = 0 ;
	if(objectsManager->levelSize.y < mapRowCount ){
		mapRowCount = objectsManager->levelSize.y;
		currentRenderOffset_y = 0;
	}else{
		// render max visible screen size
		currentRenderOffset_y = objectsManager->levelSize.y - mapRowCount - 1;// -1 cause idx start from 0
	}
	currentRenderOffset_y_copy =currentRenderOffset_y;
	printf("%i %i \n",this->mapColCount,this->mapRowCount );
}

void gameController::run(){

	while(globalState != STATES::QUIT){
		while(SDL_PollEvent( &this->event ) != 0){
			switch(this->event.type){
				case SDL_KEYDOWN :
					printf("KeyDown \n");
					this->makeMove(this->event.key.keysym.sym);
				break;
				case SDL_KEYUP:
					printf("KeyUP \n");
					this->clearMove(this->event.key.keysym.sym);
				break;
				case SDL_QUIT:
					printf("QUITING \n");
					globalState = STATES::QUIT;
				break;
			}
		}
		absoluteValueX += velocityHorizontal;
		// printf("%i \n",absoluteValueX );
		if(absoluteValueX > 0){
			absoluteValueX =0;
			continue;
		}
		this->display.clear();
		this->updateObjectsPosition();
		this->display.repaint();
		Sleep(50);
	}
}

void gameController::makeMove(SDL_Keycode & keyID){
	switch(keyID){
		case SDLK_LEFT:
		velocityHorizontal = 5;
		printf("Left pressed\n" );
		break;
		case SDLK_RIGHT:
		printf("right pressed\n" );
		velocityHorizontal = -5;
		break;
		case SDLK_UP:
		printf("up pressed\n");
		velocityVertical = 5;
		break;
		case SDLK_DOWN:
		printf("dwon pressed\n");
		velocityVertical = -5;
		break;
	}
}


void gameController::clearMove(SDL_Keycode & keyID){

	switch( keyID ){
		case SDLK_LEFT:
		case SDLK_RIGHT:
		printf("right/left released\n" );
		velocityHorizontal = 0;
		break;
		case SDLK_UP:
		case SDLK_DOWN:
		printf("up rellased\n" );
		velocityVertical = 0;
		break;
	}
}

void gameController::updateObjectsPosition(){
	for(auto &object : objectsManager->BackgroundObjects){
		object->updatePosition(velocityHorizontal,velocityVertical);
		display.appendObject(object);
	}

	for(size_t i = 0, row = 0 , col = 0,currentRenderOffset_y = currentRenderOffset_y_copy ; i < jungleItemsCount ; i++){
		auto &tileInfo = objectsManager->getJungleTileInfo(objectsManager->mapLevel[ currentRenderOffset_y * 200 + currentRenderOffset_x + col ]);
		
		this->objectsManager->visibleRenderTiles[i].setTextutreMetaData(tileInfo.cropAreaInfo);
		this->objectsManager->visibleRenderTiles[i].setPosition(col*40 , row*40);
		display.appendObject(&this->objectsManager->visibleRenderTiles[i]);
		col++;

		if(col == (mapColCount) ){
			col = 0;
			currentRenderOffset_y++;
			row++;
		}
	}			

}

gameController::~gameController(){
	delete objectsManager;
}
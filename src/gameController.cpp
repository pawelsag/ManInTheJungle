#include "gameController.h"

gameController::gameController()
{
	this->objectsManager = new objectManager( this->display.getRenderObject(), this->mapColCount, this->mapRowCount);
	this->gravityObject = gravitation(this->currentPlayerState);
	this->gravityObject.antigravityForce(2);

	this->currentRenderOffset_x = 0 ;
	this->playerX_Offset = playerStartOffset_x;
	this->playerY_Offset = playerStartOffset_y;

	if(this->objectsManager->levelSize.y < mapRowCount ){
		this->mapRowCount = this->objectsManager->levelSize.y;
		this->currentRenderOffset_y = 0;
	}else{
		// render max visible screen size
		// in case map is smaller than screen
		this->currentRenderOffset_y = this->objectsManager->levelSize.y - mapRowCount ;
	}

	this->currentRenderOffset_y_copy = this->currentRenderOffset_y;
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
					this->gravityObject.appActive = false;
				break;
			}
		}
		isMoveValid = this->validateMove();

		if( isMoveValid & MOVE_X_VALID  ){
			this->absolutePositionX += this->velocityHorizontal;
			if( this->absolutePositionX > -300 ){
				this->playerX_Offset = -this->absolutePositionX + this->playerStartOffset_x;
				this->jungleTilePosition_x = 0;
			}else{
				this->jungleTilePosition_x += this->velocityHorizontal;	

				if(this->jungleTilePosition_x < -JUNGLE_TILE_X_SIZE ){
					this->currentRenderOffset_x++;
					this->jungleTilePosition_x = TILE_CONST_SHIFT_RIGHT;
				}else if(this->jungleTilePosition_x > 0  ){
					this->currentRenderOffset_x--;
					this->jungleTilePosition_x = TILE_CONST_SHIFT_LEFT;
				}
			}			
		}
		
		this->playerY_Offset  = this->playerStartOffset_y +  this->gravityObject.getHeight();

		if( isMoveValid & MOVE_Y_VALID ){
			this->absolutePositionY += this->velocityVertical;
			this->jungleTilePosition_y += this->velocityVertical;

			if(this->jungleTilePosition_y > JUNGLE_TILE_Y_SIZE ){
				this->currentRenderOffset_y_copy--;
				this->jungleTilePosition_y = -TILE_CONST_SHIFT_RIGHT ;

			}else if(this->jungleTilePosition_y < 0 ){
				this->currentRenderOffset_y_copy++;
				this->jungleTilePosition_y = -TILE_CONST_SHIFT_LEFT ;
			}
		}

		this->display.clear();
		this->updateObjectsPosition();
		this->display.repaint();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void gameController::makeMove(SDL_Keycode & keyID){
	
	switch(keyID){
		case SDLK_LEFT:
		velocityHorizontal = ::velocity;
		currentPlayerState.setState( ST::CHARACTERSTATE::RUNLEFT );
		currentPlayerState.saveState( ST::CHARACTERSTATE::RUNLEFT );
		printf("Left pressed\n" );
		break;
		case SDLK_RIGHT:
		printf("right pressed\n" );
		currentPlayerState.setState( ST::CHARACTERSTATE::RUNRIGHT );
		currentPlayerState.saveState( ST::CHARACTERSTATE::RUNRIGHT );
		velocityHorizontal = -::velocity;
		break;
		case SDLK_UP:
		printf("up pressed\n");
		currentPlayerState.setState( ST::CHARACTERSTATE::JUMP);
		gravityObject.activateForce();
		break;
		case SDLK_DOWN:
		printf("down pressed\n");
		currentPlayerState.setState( ST::CHARACTERSTATE::LANDING);
		velocityVertical = -::velocity;
		break;
	}

}


void gameController::clearMove(SDL_Keycode & keyID){

	switch( keyID ){
		case SDLK_LEFT:
		case SDLK_RIGHT:
		printf("right/left released\n" );
		currentPlayerState.setState( ST::CHARACTERSTATE::IDLE);
		currentPlayerState.saveState( ST::CHARACTERSTATE::IDLE);
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
	// render bacground
	for(auto &object : objectsManager->BackgroundObjects){
		if(absolutePositionX < -300)
			object->updatePosition(velocityHorizontal,velocityVertical);
		else
			object->updatePosition(0,velocityVertical);

		display.appendObject(object);
	}
	// render loaded map level 
	for(size_t i = 0, row = 0 , col = 0,currentRenderOffset_y = currentRenderOffset_y_copy ; i < jungleItemsCount ; i++){
		auto &tileInfo = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ currentRenderOffset_y * 200  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ currentRenderOffset_x + col ] );

		this->objectsManager->visibleRenderTiles[i].setTextutreMetaData(tileInfo.cropAreaInfo);
		this->objectsManager->visibleRenderTiles[i].setPosition(
			col*40 + jungleTilePosition_x ,
			row*40 + jungleTilePosition_y);

		display.appendObject(&this->objectsManager->visibleRenderTiles[i]);
		col++;

		if(col == (mapColCount) ){
			col = 0;
			currentRenderOffset_y++;
			row++;
		}

	}

	// render main player
	auto player =  objectsManager->getPlayerTextureInGivenState(currentPlayerState.getState());
	player->setPosition(playerX_Offset, playerY_Offset);
	display.appendObject( player );	
}

gameController::MOVE gameController::validateMove(){
	
	MOVE state = IDLE;
	// can you move on right platform ? 
	if( absolutePositionX + velocityHorizontal <= 0 ){
		state |= MOVE::MOVE_X_VALID;
	}else
		velocityHorizontal =0;
		

	// can you move beneath level ?
	if( absolutePositionY + velocityVertical >= 0 && absolutePositionY + velocityVertical <=200 ){
		state |= MOVE::MOVE_Y_VALID;
	}else
		velocityVertical =0;
	return state;
}

gameController::~gameController(){
	delete objectsManager;
}
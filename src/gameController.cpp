#include "gameController.h"

// gravity object will prepare tile offset values
// back to old creapy rendering background
// all for now
gameController::gameController()
{
	this->objectsManager = new objectManager( this->display.getRenderObject(), this->mapColCount, this->mapRowCount);
	this->gravityObject = gravitation(this->currentPlayerState);
	this->event = new eventManager(this->currentPlayerState);

	this->gravityObject.antigravityForce(1);
	this->currentRenderOffset_x = 0 ;
	this->playerX_Offset = playerStartOffset_x;
	this->playerY_Offset = playerStartOffset_y;
	this->cameraPositionY = 200;
	if(this->objectsManager->levelSize.y < mapRowCount ){
		this->mapRowCount = this->objectsManager->levelSize.y;
		this->currentRenderOffset_y = 0;
	}else{
		// render max visible screen size
		// in case map is smaller than screen
		this->currentRenderOffset_y = this->objectsManager->levelSize.y - mapRowCount ;
	}

	this->currentRenderOffset_y_copy = this->currentRenderOffset_y;
	
}

void gameController::run(){

	while( !event->isAboutToExit ){
		
		this->checkMove();

		this->isMoveValid = this->validateMove();

		if( !(this->isMoveValid & MOVE_X_INVALID)  ){
			this->cameraPositionX  = preX_Move;
			if( this->cameraPositionX > -300 ){
				this->playerX_Offset = -this->cameraPositionX + this->playerStartOffset_x;
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

		
		if( !(this->isMoveValid & MOVE_Y_INVALID) ){
	
			this->playerY_Offset  = preY_Move;
			this->cameraPositionY -= this->velocityVertical;
			this->jungleTilePosition_y += this->velocityVertical;	

			if(this->jungleTilePosition_y > JUNGLE_TILE_Y_SIZE ){
				this->currentRenderOffset_y_copy--;
				this->jungleTilePosition_y = -TILE_CONST_SHIFT_RIGHT;
			}else if(this->jungleTilePosition_y < 0  ){
				this->currentRenderOffset_y_copy++;
				this->jungleTilePosition_y = -TILE_CONST_SHIFT_LEFT;
			}
		}
	
		// printf("%i\n",this->cameraPositionY );
		this->display.clear();
		this->updateObjectsPosition();
		this->display.repaint();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void gameController::checkMove(){
			// if left pressed set velocity
		if(this->event->isLeftPressed){
			velocityHorizontal = ::velocity;
			// if right pressed set velocity
		}else if(this->event->isRightPressed){
			velocityHorizontal = -::velocity;
			// otherwise reset velocity
		}else
			velocityHorizontal = 0;

			// if key up pressed make jump
		if(this->event->isKeyUpPressed){
			gravityObject.activateForce();
		}
	
}

void gameController::updateObjectsPosition(){
	// render bacground
	for(auto &object : objectsManager->BackgroundObjects){
		if ((this->isMoveValid & MOVE_Y_INVALID))			
			object->updatePosition(velocityHorizontal,0);
		else if(cameraPositionX < -300)
			object->updatePosition(velocityHorizontal,this->velocityVertical);
		else
			object->updatePosition(0, this->velocityVertical);

		display.appendObject(object);
	}
	// render loaded map level 
	for(size_t i = 0, row = 0 , col = 0,currentRenderOffset_y = currentRenderOffset_y_copy ; i < jungleItemsCount ; i++){
		auto &tileInfo = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ currentRenderOffset_y * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
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
	// can you move on right  ? 
	if( preX_Move + this->velocityHorizontal > 0 ){
		state |= MOVE::MOVE_X_INVALID;
		velocityHorizontal =0;
		return state;
	}else
		preX_Move += this->velocityHorizontal;

	// check if map can be moved vertcaly 
	if( false ){
		state |= MOVE::MOVE_Y_INVALID;
	}else
		this->velocityVertical = this->gravityObject.getCameraVelocity();

	this->preY_Move = this->playerStartOffset_y + this->gravityObject.getHeight();
	printf("%i\n",this->preY_Move);
	this->isPlayerInObstacle(state);
	return state;
}

// this function validate if player do not meet
// object to collide with. 
bool gameController::isPlayerInObstacle(MOVE &state){
	// position of left-up corrner of player
	
	//	player size : 60 x 80
	
	// get x postion of player 
	int x = -( (this->preX_Move) /JUNGLE_TILE_X_SIZE);
	// get y postion of player
	int y = ((this->preY_Move +20 )/JUNGLE_TILE_Y_SIZE) +currentRenderOffset_y_copy ;
	printf("%i %i\n",x, y );
	// x x x 
	// X T x <- starts here and go down
	// X P x   
	// X X x 
	// T - points to players (x,y)(letf- upper) 
	// P - player texture
	// x - other level map object
	//     potentially obstacle 
	
	// validate if player can move right

	bool isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x+1) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_X_INVALID;
		goto validateVertical;
	}

	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y+1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x+1) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_X_INVALID;	
		goto validateVertical;
	}

	// validate right corners
	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x+1) ] ).isObstacle;
	// if( isObstacle ){
	// 	state |= MOVE::MOVE_X_INVALID;
	// 	state |= MOVE::MOVE_Y_INVALID;
	// 	printf("Corner detected\n");		
	// 	goto validateVertical;
	// }


	// validate if player can move left

	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x-1) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_X_INVALID;	
		goto validateVertical;
	}

	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y+1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x-1) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_X_INVALID;
		goto validateVertical;
	}
	
	// validate left corners
	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x-1) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_X_INVALID;
		state |= MOVE::MOVE_Y_INVALID;
		goto validateVertical;
	}


	state |= MOVE::MOVE_X_VALID;
	// now validate vertical blocks 	
	validateVertical:;
	//validate if player can move 
	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x+1) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_Y_INVALID;
	}

	// validate if player can move down
	isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (y+2) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (x) ] ).isObstacle;
	if( isObstacle ){
		state |= MOVE::MOVE_DOWN_INVAID;		
	}

	if( state & MOVE::MOVE_X_INVALID ){
		this->velocityHorizontal = 0;
		this->preX_Move = this->cameraPositionX ;		
	}
	if( state & MOVE::MOVE_Y_INVALID){
		this->preY_Move = this->playerY_Offset ;
		this->gravityObject.playerColide();
	}
}

gameController::~gameController(){
	delete this->objectsManager;
	delete this->event;
}


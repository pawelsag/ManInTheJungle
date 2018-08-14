#include "gameController.h"

// game Controller Space <-- holds neccesary variables
// i don't know, if this vars should be a class members
// i'm sure i don't want use stack for passing this vars
namespace GCS{
	int x,y;
	bool isObstacle;
}

gameController::gameController()
{
	this->objectsManager = new objectManager( this->display.getRenderObject(), this->mapColCount, this->mapRowCount);
	this->gravityObject = gravitation(this->currentPlayerState);
	this->event = new eventManager(this->currentPlayerState);

	this->gravityObject.antigravityForce(0.15);
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
	
}

void gameController::run(){

	while( !event->isAboutToExit ){
		this->checkMove();
		this->currentVerticalVelocity = this->gravityObject.getHeight(this->currentVerticalVelocity);
		this->isMoveValid = this->validateMove();

		if( !(this->isMoveValid & MOVE_X_INVALID)  )
			this->callculateXOfssets();
		
		if( !(this->isMoveValid & MOVE_Y_INVALID) ){
			this->callculateYOfssets();
			// printf("%i %i\n", this->currentVerticalVelocity.currentPlayerVelocity, this->currentVerticalVelocity.currentCameraVelocity);
		}	
		// printf("%i\n",this->cameraPositionY);	
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
	int tmp_x_pos, tmp_y_pos;

	for(auto &object : objectsManager->BackgroundObjects){

		if( this ->cameraPositionY < 0)
			tmp_y_pos = CAMERA_START_Y_OFFSET;			
		else
			tmp_y_pos = -this->cameraPositionY + CAMERA_START_Y_OFFSET;

		if (cameraPositionX > -CAMERA_START_MOVE_X_OFFSET)
			tmp_x_pos = 0;
		else
			tmp_x_pos = this->cameraPositionX + CAMERA_START_MOVE_X_OFFSET - ::velocity  ;
		
		object->updatePosition(tmp_x_pos, tmp_y_pos);

		display.appendObject(object);

	}
	JungleTilesSettings tileInfo;
	// render loaded map level 
	for(size_t i = 0, row = 0 , col = 0,currentRenderOffset_y = currentRenderOffset_y_copy ; i < jungleItemsCount ; i++){
		
		if(currentRenderOffset_y < this->objectsManager->levelSize.y ) 
			tileInfo = objectsManager->getJungleTileInfo(
				objectsManager->mapLevel[ currentRenderOffset_y * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
										+ currentRenderOffset_x + col ] );
		else
			tileInfo = objectsManager->getJungleTileInfo(0x0); // if you out of screen  get transparent tiles

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
	}else
		preX_Move += this->velocityHorizontal;

	// check if map can be moved vertcaly 
    if(this ->cameraPositionY > 200 )
    	this ->cameraPositionY = 200; 
	this->velocityVertical = this->currentVerticalVelocity.currentCameraVelocity;

	this->playerStartOffset_y +=
					  this->currentVerticalVelocity.currentPlayerVelocity;

	// printf("%i \n", this->playerY_Offset );
	this->isPlayerInObstacle(state);

	return state;
}

// this function validate if player do not meet
// object to collide with. 
bool gameController::isPlayerInObstacle(MOVE &state){
	// position of left-up corrner of player
	// player size : 60 x 80
	// get x postion of player 
	GCS::x = -( (this->preX_Move-10)/JUNGLE_TILE_X_SIZE);
	// get y postion of player
	GCS::y = ((this->playerY_Offset - jungleTilePosition_y)/JUNGLE_TILE_Y_SIZE) + currentRenderOffset_y_copy;

	// variable holds temporary result of validated tile
	GCS::isObstacle = false;
	
	
	// x x x 
	// X T x <- starts here and go down
	// X P x   
	// X X x 
	// T - points to players (x,y)(letf- upper) 
	// P - player texture
	// x - other level map object
	// -.- potentially obstacle 

	if(this->event->isRightPressed)
		if(this->validateMoveRight(state) == false ){
			// if player move right and hit the wall 
			// it is impossible to hit the wall on his upper-right side
			GCS::y = ((this->playerY_Offset +20 - jungleTilePosition_y)/JUNGLE_TILE_Y_SIZE) + currentRenderOffset_y_copy;
		    GCS::isObstacle = objectsManager->getJungleTileInfo(
				objectsManager->mapLevel[ (GCS::y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
										+ (GCS::x) ] ).isObstacle;
		}else
			GCS::isObstacle = false;

	else if(this->event->isLeftPressed)
		if(this->validateMoveLeft(state) == false ){
			// if player move left and hit the wall 
			// it is impossible to hit the wall on his upper-right side
			GCS::y = ((this->playerY_Offset +20 - jungleTilePosition_y)/JUNGLE_TILE_Y_SIZE) + currentRenderOffset_y_copy;
		    GCS::isObstacle = objectsManager->getJungleTileInfo(
				objectsManager->mapLevel[ (GCS::y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
										+ (GCS::x+1) ] ).isObstacle;
		}else
			GCS::isObstacle = false;

	if( GCS::isObstacle && this->gravityObject.colision  ){
		state |= MOVE::MOVE_Y_INVALID;
		goto validateVertical_AFTER_CRUSH;
		
	}

	// if you are here the x move was valid, or there wasn't any move
	state |= MOVE::MOVE_X_VALID;

	
	// now validate vertical moves  	
	if( this->gravityObject.isForceActive() )
		if( this->validateMoveUp(state) == false){

		}else
			GCS::isObstacle = false;
	else
		this->validateMoveDown(state);


	validateVertical_AFTER_CRUSH:;
	if( state & MOVE::MOVE_X_INVALID ){
		this->velocityHorizontal = 0;
		this->preX_Move = this->cameraPositionX ;
		printf("Move x invalid\n");		
	}

	if( state & MOVE::MOVE_Y_INVALID && this->gravityObject.isForceActive()){
		this->playerStartOffset_y = this->playerY_Offset ;
		this->gravityObject.playerColide();
		printf("Move y invalid\n");

	}else if(state & MOVE::MOVE_DOWN_INVALID ){
		this->playerStartOffset_y =  this->playerY_Offset;	
		// printf("COLIDE %i %i %i\n",  this->playerY_Offset,this->cameraPositionY-200,GCS::y );
		this->gravityObject.clearJump();
		state |= MOVE::MOVE_Y_INVALID;

	}

	return true;
}


bool gameController::validateMoveLeft(MOVE &state){
// validate if player can move left

	GCS::isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (GCS::y) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (GCS::x) ] ).isObstacle;
	if( GCS::isObstacle ){
		state |= MOVE::MOVE_X_INVALID;
		return false;
	}

	GCS::isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (GCS::y+1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (GCS::x) ] ).isObstacle;
	if( GCS::isObstacle ){
		state |= MOVE::MOVE_X_INVALID;
		return false;
	}
	return true;
}

bool gameController::validateMoveRight(MOVE &state){
// validate if player can move right

	GCS::isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (GCS::y) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (GCS::x+1) ] ).isObstacle;
	if( GCS::isObstacle ){
		state |= MOVE::MOVE_X_INVALID;
		return false;
	}

	GCS::isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (GCS::y+1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (GCS::x+1) ] ).isObstacle;
	if( GCS::isObstacle ){
		state |= MOVE::MOVE_X_INVALID;	
		return false;
	}

	return true;
}

bool gameController::validateMoveUp(MOVE &state){
		GCS::y = ((this->playerY_Offset +20 - jungleTilePosition_y)/JUNGLE_TILE_Y_SIZE) + currentRenderOffset_y_copy;
	//validate if player can move up
		GCS::isObstacle = objectsManager->getJungleTileInfo(
				objectsManager->mapLevel[ (GCS::y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
										+ (GCS::x+1) ] ).isObstacle;
		if( GCS::isObstacle ){
			state |= MOVE::MOVE_Y_INVALID;
			return false;
		}
		printf("%i \n",GCS::x);
		GCS::isObstacle = objectsManager->getJungleTileInfo(
				objectsManager->mapLevel[ (GCS::y-1) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
										+ (GCS::x) ] ).isObstacle;
		if( GCS::isObstacle ){
			state |= MOVE::MOVE_Y_INVALID;
			return false;
		}

	return true;
}

bool gameController::validateMoveDown(MOVE &state){
	// validate if player can move down
	printf("%i %i %i\n",playerY_Offset, currentRenderOffset_y_copy ,GCS::x );
	
	GCS::isObstacle = objectsManager->getJungleTileInfo(
			objectsManager->mapLevel[ (GCS::y+2) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
									+ (GCS::x) ] ).isObstacle;
	if( GCS::isObstacle) {
		state |= MOVE::MOVE_DOWN_INVALID;
		return false;
	}

	GCS::isObstacle = objectsManager->getJungleTileInfo(
		objectsManager->mapLevel[ (GCS::y+2) * this->objectsManager->levelSize.x  //  (200 /  JUNGLE_TILE_X_SIZE) = 5 <- y_offset in render map 
								+ (GCS::x+1) ] ).isObstacle;
	if( GCS::isObstacle) {
		state |= MOVE::MOVE_DOWN_INVALID;
		return false;
	}
 	return true;
}

void gameController::callculateXOfssets(){
	this->cameraPositionX  = this->preX_Move;
	if( this->cameraPositionX > -CAMERA_START_MOVE_X_OFFSET ){
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

void gameController::callculateYOfssets(){
	this->playerY_Offset  = this->playerStartOffset_y;
	this->cameraPositionY -= this->velocityVertical;
	this->jungleTilePosition_y += this->velocityVertical;	
	if(this->jungleTilePosition_y > JUNGLE_TILE_Y_SIZE ){
		this->currentRenderOffset_y_copy--;
		this->jungleTilePosition_y = -TILE_CONST_SHIFT_RIGHT;
	}else if(this->jungleTilePosition_y < 0  ){
		this->currentRenderOffset_y_copy++;
		this->jungleTilePosition_y = -TILE_CONST_SHIFT_LEFT;
	}
	// printf(" %i\n",this->currentRenderOffset_y_copy );
}

gameController::~gameController(){
	delete this->objectsManager;
	delete this->event;
}


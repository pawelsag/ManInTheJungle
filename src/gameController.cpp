#include "gameController.h"

gameController::gameController(){
	objects = new objectManager( this->display.getRenderObject() );
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
	for(auto &object : objects->BackgroundObjects){
		object->updatePosition(velocityHorizontal,velocityVertical);
		display.appendObject(object);
	}

}

gameController::~gameController(){
	delete objects;
}
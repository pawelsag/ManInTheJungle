#include "eventManager.h"
#include "gameController.h"

eventManager::eventManager(textureStateManager & textureManager)
	:isAboutToExit{false},
	currentPlayerStatePtr(&textureManager),
	eventManagerThread(&eventManager::run,this)
{
	this->isKeyUpPressed = this->iskeyDownPressed =false;
	this->isLeftPressed = this->isRightPressed = false;
	
	printf("event loop started\n");
}

eventManager::~eventManager(){
	eventManagerThread.join();
}

void eventManager::run(){
	while( !isAboutToExit ){
		
		while(SDL_PollEvent( &this->event ) != 0){

				switch(this->event.type){
					case SDL_KEYDOWN :
						this->makeMove(this->event.key.keysym.sym);
					break;
					case SDL_KEYUP:
						this->clearMove(this->event.key.keysym.sym);
					break;
					case SDL_QUIT:
						printf("QUITING \n");
						this->isAboutToExit = true;
					break;
				}
			}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

void eventManager::makeMove(SDL_Keycode & keyID){
	
	switch(keyID){
		case SDLK_LEFT:
			this->isRightPressed = false;
			this->isLeftPressed = true;
			currentPlayerStatePtr->setState( ST::CHARACTERSTATE::RUNLEFT );
			currentPlayerStatePtr->saveState( ST::CHARACTERSTATE::RUNLEFT );
			currentPlayerStatePtr->jumpDirection = ST::CHARACTERSTATE::JUMPLEFT;
			currentPlayerStatePtr->landingDirection = ST::CHARACTERSTATE::LANDINGLEFT;
			
		break;
		case SDLK_RIGHT:
			this->isLeftPressed = false;
			this->isRightPressed = true;
			currentPlayerStatePtr->setState( ST::CHARACTERSTATE::RUNRIGHT );
			currentPlayerStatePtr->saveState( ST::CHARACTERSTATE::RUNRIGHT );
			currentPlayerStatePtr->jumpDirection = ST::CHARACTERSTATE::JUMP;
			currentPlayerStatePtr->landingDirection = ST::CHARACTERSTATE::LANDING;
			
		break;
		case SDLK_UP:
			this->iskeyDownPressed = false;
			this->isKeyUpPressed = true;

		break;
		case SDLK_DOWN:
			this->iskeyDownPressed = true;
			currentPlayerStatePtr->setState( ST::CHARACTERSTATE::SPECIAL);
		break;
	}

}


void eventManager::clearMove(SDL_Keycode & keyID){

	switch( keyID ){
		case SDLK_LEFT:
			this->isLeftPressed = false;
			currentPlayerStatePtr->setState( ST::CHARACTERSTATE::IDLE);
			currentPlayerStatePtr->saveState( ST::CHARACTERSTATE::IDLE);
		break;
		case SDLK_RIGHT:
			this->isRightPressed = false;
			currentPlayerStatePtr->setState( ST::CHARACTERSTATE::IDLE);
			currentPlayerStatePtr->saveState( ST::CHARACTERSTATE::IDLE);
		break;
		case SDLK_UP:
			this->isKeyUpPressed = false;
		break;
		case SDLK_DOWN:
			this->iskeyDownPressed = false;
			currentPlayerStatePtr->restoreState();
		break;
	}
}
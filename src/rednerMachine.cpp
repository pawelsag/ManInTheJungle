#include "rednerMachine.h"
#include "globalSettings.h"
#include <assert.h>
#include <stdio.h>
 
rednerMachine::rednerMachine(SDL_Window * windowHandle){
	if(windowHandle == nullptr){
		
		if(SDL_Init(SDL_INIT_VIDEO) < 0){
			printf("SDL_Init failed: %s\n", SDL_GetError());
			return;
		}
		
		this->windowHandle = SDL_CreateWindow( "SOMETHING", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if(this->windowHandle == nullptr){
			printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
			return;
		}

	}else
		this->windowHandle = windowHandle; 


	this->renderObj =  SDL_CreateRenderer( this->windowHandle, -1, SDL_RENDERER_ACCELERATED );
	
	if(this->renderObj == NULL){
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError() );
		return;
	}

	if((!(IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG) )){
		printf("SDL_CreateRenderer failed: %s\n", SDL_GetError() );
		return;
	}

	SDL_RenderClear( this->renderObj );
}

void rednerMachine::appendObject(renderObject * obj){
	if( obj == nullptr ){
		return;
	}
	this->renderBuffer.push_back(obj);
}

void rednerMachine::removeObject(int offset){
	if( (unsigned int)offset < this->renderBuffer.size() || offset < 0)
		return;

	this->renderBuffer.erase( this->renderBuffer.begin() + offset);
}

void rednerMachine::repaint(){

	for(auto & object : this->renderBuffer){
		
		if(object->position.readyToRender == false)
			continue;
		this->dstRenderSquare.x = object->position.x_offset;
		this->dstRenderSquare.y = object->position.y_offset;
		this->dstRenderSquare.w = object->position.width;
		this->dstRenderSquare.h = object->position.height;
		SDL_RenderCopy( this->renderObj, (*(object->sprite))[object->renderTxtId],&object->cropedTexture[object->cropId],&this->dstRenderSquare );	
	}
	
	SDL_RenderPresent( this->renderObj );
}
#include "renderObject.h"
#include <stdio.h>
#include <stdlib.h>
renderObject::renderObject(int x, int y, int width, int height){
	this->position = TextureRenderPosition(x,y,width,height);
	this->sprite = std::make_shared<TextureVector>();
}

renderObject::renderObject(TextureRenderPosition & positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture){
	this->sprite = std::make_shared<TextureVector>();
	this->position = positionInfo ;
	this->sprite->push_back( &texture );
	this->cropedTexture = std::make_unique<SDL_Rect>(textureParam);
}
renderObject::renderObject(renderObject *object){
	if(this == object)
		return;
	if(object->sprite != nullptr)
		this->sprite = object->sprite;

	if(object->cropedTexture != nullptr)
		this->cropedTexture = std::make_unique<SDL_Rect>( *object->cropedTexture );
	
	this->position = object->position;
	this->textType = object->textType;
	

}
renderObject::renderObject(renderObject &object){
	if(this == &object)
		return;
	if(object.sprite != nullptr)
		this->sprite = object.sprite;

	if(object.cropedTexture != nullptr)
		this->cropedTexture = std::make_unique<SDL_Rect>( *object.cropedTexture );
	
	this->position = object.position;
	this->textType = object.textType;
}

renderObject::renderObject(renderObject &&object){
	if(object.sprite != nullptr)
		this->sprite = object.sprite;

	if(object.cropedTexture != nullptr)
		this->cropedTexture = std::make_unique<SDL_Rect>( *object.cropedTexture );
	
	this->position = object.position;
	this->textType = object.textType;
}

bool renderObject::loadTexturesFromFile( const std::string && fileName, SDL_Renderer & renderObj){
	SDL_Surface * loadedSurface = IMG_Load(fileName.c_str());
	printf("%s\n", fileName.c_str());
	if(loadedSurface == NULL ){
		printf("IMG_Load failed: %s\n", SDL_GetError());
		return false;
	}
	
	this->sprite->push_back( SDL_CreateTextureFromSurface(&renderObj, loadedSurface) );
	SDL_FreeSurface( loadedSurface );
	return true;
}

void renderObject::setLoadedTexture(const renderObject & instance){
	this->sprite = instance.sprite;
}

void renderObject::setLoadedTexture(SDL_Texture & texture){
	this->sprite->push_back(&texture);
}

void renderObject::setTextutreMetaData(SDL_Rect & textureParams){
	this->cropedTexture = std::make_unique<SDL_Rect>(textureParams);
}

void renderObject::setTextutreMetaData(int x,int y, int w, int h){
	this->cropedTexture = std::make_unique<SDL_Rect>();
	this->cropedTexture->x = x;
	this->cropedTexture->y = y;
	this->cropedTexture->w = w;
	this->cropedTexture->h = h;
}

void renderObject::updatePosition(int x, int y){
		this->position.x_offset += x;
		this->position.y_offset += y;
}

renderObject::~renderObject(){

}
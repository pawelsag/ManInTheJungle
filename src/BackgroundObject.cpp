#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(int x, int y, int width, int height)
	:renderObject(x,y,width,height)
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
BackgroundObject & BackgroundObject::operator=( BackgroundObject& instance ){

	renderObject::operator=(instance);
	return *this;
}
BackgroundObject & BackgroundObject::operator=( BackgroundObject&& instance ){

	renderObject::operator=(instance);
	return *this;
}

BackgroundObject::BackgroundObject(BackgroundObject & instance)
:renderObject(instance)
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
BackgroundObject::BackgroundObject(renderObject && instance)
:renderObject( std::move(instance) )
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
BackgroundObject::BackgroundObject(BackgroundObject * instance)
:renderObject(instance)
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
BackgroundObject::BackgroundObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture)
	:renderObject(positionInfo, textureParam,std::move(texture) )
{
	this->textType = TEXTURETYPE::BACKGROUND;
}

void BackgroundObject::updatePosition(int x, int y){
	// this realy suck
	this->position.x_offset += x ;
	
	this->position.y_offset += y;
	
	// printf("%i\n", this->position.y_offset);
	if(this->position.x_offset <= -SCREEN_WIDTH ){
		this->position.x_offset = SCREEN_WIDTH  ;
	}
	
	if(this->position.x_offset > SCREEN_WIDTH ){
		this->position.x_offset = -SCREEN_WIDTH + velocity;
	}   
}

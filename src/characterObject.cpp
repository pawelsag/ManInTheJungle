#include "characterObject.h"

characterObject::characterObject(int x, int y, int width, int height)
	:renderObject(x,y,width,height)
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
characterObject & characterObject::operator=( characterObject& instance ){

	renderObject::operator=(instance);
	return *this;
}
characterObject::characterObject(characterObject & instance)
:renderObject(instance)
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
characterObject::characterObject(renderObject && instance)
:renderObject( std::move(instance) )
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
characterObject::characterObject(characterObject * instance)
:renderObject(instance)
{
	this->textType = TEXTURETYPE::BACKGROUND;
}
characterObject::characterObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture)
	:renderObject(positionInfo, textureParam,std::move(texture) )
{
	this->textType = TEXTURETYPE::BACKGROUND;
}

void characterObject::updatePosition(int x, int y){
	
	this->position.x_offset += x;
	this->position.y_offset += y;
	
	// printf("%i %i\n", this->position.x_offset , this->position.x_beginOffset);
	if(this->position.x_offset <= -SCREEN_WIDTH ){
		this->position.x_offset = SCREEN_WIDTH  ;
	}
	
	if(this->position.x_offset > SCREEN_WIDTH ){
		this->position.x_offset = -SCREEN_WIDTH + 5;
	}   
}

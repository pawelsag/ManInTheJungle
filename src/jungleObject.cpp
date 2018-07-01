#include "jungleObject.h"
jungleObject::jungleObject(int x, int y, int width, int height, unsigned int code)
	:renderObject(x,y,width,height)
{
	this->textType = TEXTURETYPE::OBSTACLE;
	this->texture_code = code;
}

jungleObject::jungleObject(jungleObject & instance)
:renderObject(instance)
{
	this->textType = TEXTURETYPE::OBSTACLE;
	this->texture_code  = instance.texture_code;
}
jungleObject::jungleObject(jungleObject && instance)
:renderObject( std::move(instance) )
{
	this->textType = TEXTURETYPE::OBSTACLE;
	this->texture_code  = instance.texture_code;
}
jungleObject::jungleObject(jungleObject * instance)
:renderObject(instance)
{
	this->textType = TEXTURETYPE::OBSTACLE;
	this->texture_code  = instance->texture_code;
}
jungleObject::jungleObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture, unsigned int code)
	:renderObject(positionInfo, textureParam,std::move(texture) )
{
	this->textType = TEXTURETYPE::OBSTACLE;
	this->texture_code = code;
}

void jungleObject::updatePosition(int x, int y){
	
	this->position.x_offset += x;
	this->position.y_offset -= y;
	
	// printf("%i %i\n", this->position.x_offset , this->position.x_beginOffset);
	if(this->position.x_offset <= -SCREEN_WIDTH ){
		this->position.x_offset = SCREEN_WIDTH;
	}
	if(this->position.x_offset > SCREEN_WIDTH ){
		this->position.x_offset = -SCREEN_WIDTH+5;
	}   
}
jungleObject::~jungleObject(){}
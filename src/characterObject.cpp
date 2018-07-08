#include "characterObject.h"

characterObject::characterObject(int x, int y, int width, int height,ST::CHARACTERSTATE State)
	:renderObject(x,y,width,height)
{
	this->state = State;
}
characterObject & characterObject::operator=( characterObject& instance ){

	renderObject::operator=(instance);
	this->state = instance.state;

	return *this;
}
characterObject & characterObject::operator=( characterObject&& instance ){

	renderObject::operator=(instance);
	this->state = instance.state;

	return *this;
}

characterObject::characterObject(characterObject & instance)
:renderObject(instance)
{
	this->state = instance.state;
}
characterObject::characterObject(characterObject && instance)
:renderObject( std::move(instance) )
{
	this->state = instance.state;
}
characterObject::characterObject(characterObject * instance)
:renderObject(instance)
{
	this->state = instance->state;
}
characterObject::characterObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture,ST::CHARACTERSTATE State)
	:renderObject(positionInfo, textureParam,std::move(texture) )
{
	this->state = State;
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

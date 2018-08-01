#include "jungleObject.h"

jungleObject::jungleObject(int x, int y, int width, int height, unsigned char code, TEXTURETYPE txType)
	:renderObject(x,y,width,height)
{
	this->cropedTexture.push_back({0,0,width,height});
	this->textType = txType;
	this->texture_code = code;
}

jungleObject::jungleObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture, unsigned char code, TEXTURETYPE txType)
	:renderObject(positionInfo, textureParam,std::move(texture) )
{
	this->textType = txType;
	this->texture_code = code;
}

jungleObject::jungleObject(jungleObject & instance)
:renderObject(instance)
{
	this->textType = instance.textType;
	this->texture_code  = instance.texture_code;
}
jungleObject::jungleObject(jungleObject && instance)
:renderObject( std::move(instance) )
{
	this->textType = instance.textType;
	this->texture_code  = instance.texture_code;
}

jungleObject::jungleObject(jungleObject * instance)
:renderObject(instance)
{
	this->textType = instance->textType;
	this->texture_code  = instance->texture_code;
}


jungleObject & jungleObject::operator=( jungleObject& instance ){
	
	renderObject::operator=(instance);
	texture_code = instance.texture_code;

	return *this;
}

jungleObject & jungleObject::operator=( jungleObject&& instance ){
	
	renderObject::operator=(instance);
	texture_code = instance.texture_code;

	return *this;
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
void jungleObject::setTextutreMetaData( int x,int y, int w, int h ){
	SDL_Rect tmp{x,y,w,h};
	this->cropedTexture[0] = tmp; 
}

void jungleObject::setTextutreMetaData( const SDL_Rect & textureParams ){
	this->cropedTexture[0] = textureParams;	
}


jungleObject::~jungleObject(){}
#include "renderObject.h"
#include <stdio.h>
#include <stdlib.h>
renderObject::renderObject(int x, int y, int width, int height){
	this->position = TextureRenderPosition(x,y,width,height);
	this->sprite = std::make_shared<PType::TextureVector>();
	
}

renderObject::renderObject(TextureRenderPosition & positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture){
	this->sprite = std::make_shared<PType::TextureVector>();
	this->position = positionInfo ;
	this->sprite->push_back( &texture );
	this->cropedTexture.push_back( textureParam );
}
renderObject::renderObject(renderObject *object){
	if(this == object)
		return;
	if(object->sprite != nullptr)
		this->sprite = object->sprite;

	
	this->cropedTexture = object->cropedTexture ;
	
	this->position = object->position;
	this->textType = object->textType;
	

}
renderObject::renderObject(renderObject &object){
	if(this == &object)
		return;
	if(object.sprite != nullptr)
		this->sprite = object.sprite;

	this->cropedTexture = object.cropedTexture ;
	
	this->position = object.position;
	this->textType = object.textType;
}

renderObject::renderObject(renderObject &&object){
	if(object.sprite != nullptr)
		this->sprite = object.sprite;

	this->cropedTexture =  object.cropedTexture;
	
	this->position = object.position;
	this->textType = object.textType;
}
renderObject & renderObject::operator=(renderObject & instance){
	if(this == &instance)
		return *this;
	if(instance.sprite != nullptr)
		this->sprite = instance.sprite;
	
	this->cropedTexture = instance.cropedTexture;
	this->position = instance.position;
	this->textType = instance.textType;
	
	return *this;
}
renderObject & renderObject::operator=(renderObject && instance){
	
	if(instance.sprite != nullptr)
		this->sprite = instance.sprite;
	
	this->cropedTexture = instance.cropedTexture;
	this->position = instance.position;
	this->textType = instance.textType;
	
	return *this;
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

void renderObject::setTextutreMetaData(const SDL_Rect & textureParams){
	this->cropedTexture.push_back(textureParams);

}
void renderObject::generateCropArea(int n, int w, int h){
	int txWidth, txHeight;
	SDL_QueryTexture((*this->sprite)[0],NULL,NULL,&txWidth,&txHeight);
	SDL_Rect area;
	// spli to n sub areas
	for(int i =0,j=0,k=0 ;i <n; i++){
		area.x= w*j;
		area.y = h*k;
		area.w = w;
		area.h = h;
		cropedTexture.push_back(area);
		if(w*j == txWidth){
			j = 0;
			k++;
		}	
	}

}
void renderObject::setTextutreMetaData(int x,int y, int w, int h){
	SDL_Rect temp;
	temp.x = x;
	temp.y = y;
	temp.w = w;
	temp.h = h;
	this->cropedTexture.push_back(temp);
}

void renderObject::updatePosition(int x, int y){
		this->position.x_offset += x;
		this->position.y_offset += y;
}

renderObject::~renderObject(){

}
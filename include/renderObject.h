#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "globalSettings.h"
#include <memory>
#include "customTypes.h"
#ifndef RENDEROBJECT
#define RENDEROBJECT



class renderObject
{
	friend class rednerMachine;

protected:
	// variable used only when object conatains texture sets
	// it is used to animate each sprite
	int renderTxtId{0};
	// vraible controls currently displayed croped area
	int cropId{0};
	// informs about divided textures areas count
	int cropAreaAmount{0};
	// keep info about texture internal data
	// use this structure to crope asset
	// you can set position
	PType::RectVector cropedTexture;
	// ponter to texture pointer
	PType::TextureVector_Ptr sprite{nullptr};
	// keep info about texture positions
	TextureRenderPosition position;
	TEXTURETYPE textType;

public:
	//create default object without texture and position
	renderObject(){};
	// contruct object with given position and size
	renderObject(int x, int y, int width, int height);
	// contruct new obejct with given position and texture
	renderObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture);
	renderObject( renderObject *object);
	renderObject( renderObject &object);
	renderObject( renderObject &&object);
	virtual renderObject & operator=( renderObject& instance );
	virtual renderObject & operator=( renderObject&& instance );

	bool loadTexturesFromFile( const std::string && fileName,  SDL_Renderer & renderObj);
	virtual void setLoadedTexture(const renderObject & instance);
	virtual void setLoadedTexture(SDL_Texture & texture);
	// set textture internal croped meta info
	virtual void setTextutreMetaData( int x,int y, int w, int h );
	virtual void setTextutreMetaData( const SDL_Rect & textureParams );
	// split area with given height and width with additional dellimiter
	virtual void generateCropArea(int n, int w, int h);
	// modify object postion at given id
	virtual void updatePosition( int x , int y );

	virtual unsigned char getCode()const{
		return 0;
	}

	~renderObject();

	// inline functions
	inline size_t getObjectsCount(){
		return this->sprite->size();
	}

	inline const TextureRenderPosition& getObjectPostionInfo() {
		return this->position;
	}
	// append new position to the position vector
	inline void setPosition(int x, int y){
		position.x_offset =x;
		position.y_offset =y;
	}
	inline void setBeginPosition(int x, int y){
		this->position.x_beginOffset = x;
		this->position.y_beginOffset = y;

	}

	inline void setPosition(TextureRenderPosition &positionInfo){
		this->position = positionInfo;
	}

	inline void resetRenderedFrame(){
		this->cropId = 0 ;
		this->renderTxtId =0;
	}
};

#endif
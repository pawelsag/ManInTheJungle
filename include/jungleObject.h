#ifndef JUNGLEOBJECT
#define JUNGLEOBJECT

#include "renderObject.h"

class jungleObject :public renderObject
{

private:
	unsigned char texture_code;
public:
	//create default object without texture and position
	jungleObject()=default;
	// contruct object with given position and size
	jungleObject(int x, int y, int width, int height, unsigned char code, TEXTURETYPE txType = TEXTURETYPE::OBSTACLE );
	// contruct new obejct with given position and texture
	jungleObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture, unsigned char code, TEXTURETYPE txType = TEXTURETYPE::OBSTACLE);
	jungleObject( jungleObject *object);
	jungleObject( jungleObject &object);
	jungleObject( jungleObject &&object);
	~jungleObject();
	jungleObject & operator=( jungleObject& instance );
	jungleObject & operator=( jungleObject&& instance );
	void setTextutreMetaData( int x,int y, int w, int h );
	void setTextutreMetaData( const SDL_Rect & textureParams );

	inline unsigned char getCode()const{
		return this->texture_code;
	}
	inline void changeTextureType(TEXTURETYPE txType){
		this->textType = txType;
	}

	void updatePosition( int x , int y );
};

#endif
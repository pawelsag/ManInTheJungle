#ifndef JUNGLEOBJECT
#define JUNGLEOBJECT

#include "renderObject.h"

class jungleObject :public renderObject
{

private:
	unsigned int texture_code; 
public:
	//create default object without texture and position 
	jungleObject()=default;
	// contruct object with given position and size
	jungleObject(int x, int y, int width, int height, unsigned int code);
	// contruct new obejct with given position and texture
	jungleObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture, unsigned int code);
	jungleObject( jungleObject *object);
	jungleObject( jungleObject &object);
	jungleObject( jungleObject &&object);
	~jungleObject();


	void updatePosition( int x , int y );
};

#endif
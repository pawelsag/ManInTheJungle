#ifndef CHARACTEROBJECT
#define CHARACTEROBJECT

#include "renderObject.h"
class characterObject : renderObject{

	enum CHARACTERSTATE{
		IDLE,
		JUMP,
		RUNLEFT,
		RUNRIGHT,		
	};
public:
	const CHARACTERSTATE state;
	characterObject() = delete;
	characterObject(int x, int y, int width, int height, CHARACTERSTATE s);
	characterObject(characterObject * instance);
	characterObject(characterObject & instance);
	characterObject(renderObject && instance);
	characterObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture);
	
	characterObject & operator=( characterObject& instance );

	~characterObject();
	void updatePosition(int x, int y);

}

#endif
#ifndef CHARACTEROBJECT
#define CHARACTEROBJECT

#include "renderObject.h"
class characterObject :public renderObject{


public:
	ST::CHARACTERSTATE state;
	characterObject() = default;
	characterObject(int x, int y, int width, int height, ST::CHARACTERSTATE State);
	characterObject(characterObject * instance);
	characterObject(characterObject & instance);
	characterObject(characterObject && instance);
	characterObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture,ST::CHARACTERSTATE State);

	characterObject & operator=( characterObject& instance );
	characterObject & operator=( characterObject&& instance );

	~characterObject(){};
	void updatePosition(int x, int y);

	inline void renderNextFrame(){
		if( this->cropId >= this->cropAreaAmount-1 )
			this->cropId = 0;
		else
			this->cropId++;


	}

};

#endif
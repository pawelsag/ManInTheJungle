#ifndef BACKGROUNDOBJECT
#define BACKGROUNDOBJECT
#include <stdint.h>
#include "renderObject.h"
/* 
	class hold background textures 
	to render smooth move i need two sets of textures
	When render approaching  the edge, i glue second texture to the first and vice versa
	
*/
class BackgroundObject : public renderObject
{
public:
	BackgroundObject() = delete;
	BackgroundObject(int x, int y, int width, int height);
	BackgroundObject(BackgroundObject * instance);
	BackgroundObject(BackgroundObject & instance);
	BackgroundObject(renderObject && instance);
	BackgroundObject(TextureRenderPosition &positionInfo, SDL_Rect & textureParam ,SDL_Texture &&texture);
	
	
	BackgroundObject & operator=( BackgroundObject& instance );

	~BackgroundObject();
	void updatePosition(int x, int y);
	// bool loadTexturesFromFile( const std::string && fileName, SDL_Renderer & renderObj);
private:
	uint8_t textureRenderId {0};
};

#endif
#include <SDL2/SDL.h>
#ifndef CUSTOMTEXTURES
#define CUSTOMTEXTURES

struct TextureRenderPosition{
	int x_offset, y_offset;
	const int x_beginOffset, y_beginOffset;
	int width, height;
	bool readyToRender;
	//default contructor 
	TextureRenderPosition()
	:x_beginOffset(0),y_beginOffset(0)  
	{
		x_offset = y_offset = width = height =0;
		readyToRender = false;
	}
	TextureRenderPosition(int x, int y, int w, int h)
	:x_beginOffset(x),y_beginOffset(y)  
	{
		x_offset = x;
		y_offset = y;
		width = w;
		height = h;
		readyToRender = true;
	}
	// copy constructor
	TextureRenderPosition(TextureRenderPosition  &pos)
	:x_beginOffset(pos.x_beginOffset),y_beginOffset(pos.y_beginOffset)  
	{
		x_offset = pos.x_offset;
		y_offset = pos.y_offset;
		width = pos.width;
		height = pos.height;
		readyToRender = pos.readyToRender;
	}

	// move constructor
	TextureRenderPosition(TextureRenderPosition  &&pos)
	:x_beginOffset(pos.x_beginOffset),y_beginOffset(pos.y_beginOffset)  
	{
		x_offset = pos.x_offset;
		y_offset = pos.y_offset;
		width = pos.width;
		height = pos.height;
		readyToRender = pos.readyToRender;
	}
	// copy assigment
	 TextureRenderPosition& operator=(TextureRenderPosition & pos)
	 {
		if(this == &pos )
			return *this;
		// remove const and assign value
		int &x =  const_cast<int&>(this->x_beginOffset);
		x = pos.x_beginOffset;

		int &y =  const_cast<int&>(this->y_beginOffset);
		y = pos.y_beginOffset;

		x_offset = pos.x_offset;
		y_offset = pos.y_offset;
		width = pos.width;
		height = pos.height;
		readyToRender = pos.readyToRender;
		return pos;
	}
	// move assigment
	TextureRenderPosition& operator=(TextureRenderPosition && pos){
		x_offset = pos.x_offset;
		y_offset = pos.y_offset;

		// remove const and assign value
		int &x =  const_cast<int&>(this->x_beginOffset);
		x = pos.x_beginOffset;

		int &y =  const_cast<int&>(this->y_beginOffset);
		y = pos.y_beginOffset;

		width = pos.width;
		height = pos.height;
		readyToRender = pos.readyToRender;
		return *this;
	}
};

struct basicRenderObject{
	TextureRenderPosition *pos;
	SDL_Texture *texture;
	SDL_Rect * textureMetaData;
};


#endif
#include <SDL2/SDL.h>
#include <string>

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

struct JungleTilesSettings{
	unsigned char code;
	SDL_Rect cropAreaInfo;
	JungleTilesSettings(unsigned char code, int x, int y, int w, int h){
		this->code =  code;
		this->cropAreaInfo.x = x;
		this->cropAreaInfo.y = y;
		this->cropAreaInfo.w = w;
		this->cropAreaInfo.h = h;
	}
	JungleTilesSettings(unsigned char code, SDL_Rect & cropedArea){
		this->code =  code;
		this->cropAreaInfo.x = cropedArea.x;
		this->cropAreaInfo.y = cropedArea.y;
		this->cropAreaInfo.w = cropedArea.w;
		this->cropAreaInfo.h = cropedArea.h;
	}

};

enum STATES{
	ACTIVE,
	QUIT
};
enum TEXTURETYPE{
	BACKGROUND,
	CHARACTER,
	BOT,
	OBSTACLE
};

namespace ST{
	enum CHARACTERSTATE{
		IDLE=0,
		JUMP,
		RUNLEFT,
		RUNRIGHT,
		LANDING,
		HANG,
		JUMPLEFT,
		LANDINGLEFT,
		//special must be last stet in this enum type
		// becouse based on him i count amount of elemnts in enum type
		SPECIAL
	};
	constexpr const int STATE_COUNT = CHARACTERSTATE::SPECIAL + 1; 

	struct CHARACTERSTATE_INFO{
		const char * TextureName;
		CHARACTERSTATE State;
		// Since there are diffrent settings for each characterTexture
		// n -- number of diffrent texture poses
		// w,h -- width and height for each pose
		int n, w, h ;
		CHARACTERSTATE_INFO(const char * name, CHARACTERSTATE state, int _n, int _w, int _h)
		:TextureName(name),State(state),n(_n),w(_w),h(_h){}
	};
};
struct containerSize{
	size_t x,y;
};

#endif
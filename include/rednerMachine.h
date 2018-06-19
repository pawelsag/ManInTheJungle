#include "renderObject.h"
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef RENDERMACHNE
#define RENDERMACHNE

class rednerMachine
{

	std::vector<renderObject *> renderBuffer;
	SDL_Window *windowHandle{nullptr};
	SDL_Renderer * renderObj{nullptr};
	SDL_Rect dstRenderSquare;

public:
	explicit rednerMachine(SDL_Window * windowHandle = nullptr);

	void removeObject( int offset );
	void appendObject(renderObject * obj);
	void repaint();
	

	// inline fucntions

	inline void clear(){
		this->renderBuffer.clear();
		SDL_RenderClear(this->renderObj);
		
	}

	inline SDL_Renderer & getRenderObject(){
		return *this->renderObj;
	};
	
	~rednerMachine(){};

};

#endif
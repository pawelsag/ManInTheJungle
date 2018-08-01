#ifndef GRAVITATION
#define GRAVITATION
#include <vector>
#include "textureStateManager.h"
#include <stdio.h>
class gameController;

constexpr const int gravityValuesCount =20;

class gravitation
{
	friend class gameController;

	int counter{0};
	float forceStrength{0};
	bool counterForceActive{ false },colision{true};
	textureStateManager * stateInstancePtr;	
	std::vector<int> playerHeight;

public:
	gravitation()=default;
	gravitation(textureStateManager & stateObject);
	~gravitation()=default;
	
	void antigravityForce(int strength);
	int getHeight();

	inline float gravityEqeuation(int x) {
		// a(x-10)(x+10)
		return this->forceStrength * (x-10)*(x+10) ;
	}

	inline void activateForce(){
		this->counterForceActive = true;
	}
	
	inline const bool isForceActive()const{
		return this->counterForceActive && (this->counter < 11);
	}

	inline int getCameraVelocity(){
		if(this->counterForceActive == false  )
			return -20;
		// printf("%i \n", this->counter );		
		if(this->counter < 11 )
			return 10;
		else 
			return -10;
		
	}
	inline void playerColide(){
		if( colision ){
			this->counter = (this->playerHeight.size() - this->counter);
			if(this->counter < 10)
				this->counter = this->playerHeight.size() - this->counter;
			this-> counter+=2;
			this->colision = false;
			printf("Colision %i\n",this->counter);
		}
	}

}; 

#endif
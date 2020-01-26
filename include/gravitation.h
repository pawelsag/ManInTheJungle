#ifndef GRAVITATION
#define GRAVITATION
#include <vector>
#include "textureStateManager.h"
#include <stdio.h>

class gameController;

constexpr const int gravityValuesCount =20;

class gravitation
{
public:
	struct gravityDetails{
		int currentPlayerVelocity;
		int currentCameraVelocity;
	};

private:
	friend class gameController;

	int counter{0}, k{0};
	float forceStrength{0};
	bool counterForceActive{ false },colision{true};
	textureStateManager * stateInstancePtr;
	std::vector<int> playerHeight;
	// gravityValuesCount+1 we want exacly the same amount of values as in playerHeight
	std::vector<int> flatEarthGravity = std::vector<int>(gravityValuesCount+1, 0); //{0, 0, 0, 0 ...} 20 x 0


public:
	gravitation()=default;
	gravitation(textureStateManager & stateObject);
	~gravitation()=default;

	void antigravityForce(float strength);
	gravityDetails&  getHeight(gravityDetails& currentVerticalVelocity);

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
	inline void clearJump(){
		this->counter = 0;
		this->colision = true;
		this->counterForceActive = false;
		this->stateInstancePtr->restoreState();

	}
	inline void playerColide(){
		if( colision ){
			// calculate offset of the heigth to restore begin position
			// it is associated with substract same value as it was added to
			// player position
			this->counter = (gravityValuesCount - this->counter);
			if(this->counter < 10)
				this->counter = gravityValuesCount- this->counter;
			this->counter+=2;
			this->colision = false;
			printf("Colision %i\n",this->counter);
		}
	}

};

#endif
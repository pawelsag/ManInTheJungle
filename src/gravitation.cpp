#include "gravitation.h"
#include <math.h>
#include "gameController.h"

gravitation::gravitation(textureStateManager & stateObject){
	this->stateInstancePtr = &stateObject;
}

void gravitation::antigravityForce(int strength){
	if(counterForceActive != true){
		this->forceStrength = strength;
		this->height.clear();
		for(int x = -10, k=0; k <= gravityValuesCount; x++, k++ )
			height.push_back( gravityEqeuation( x ) );
	}
}

int gravitation::getHeight(){
	if(this->counterForceActive == false)
		return 0;

	if(this->counter > 11)
		this->stateInstancePtr->currentPlayerState = this->stateInstancePtr->jumpDirection;
	else
		this->stateInstancePtr->currentPlayerState = this->stateInstancePtr->landingDirection;

	if( this->counter > 20 ){
		this->counter = 0;
		this->counterForceActive = false;
		this->stateInstancePtr->restoreState();

	}

	return this->height[this->counter++];
}

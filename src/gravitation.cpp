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

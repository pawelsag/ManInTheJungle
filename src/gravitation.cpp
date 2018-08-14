#include "gravitation.h"
#include <math.h>
#include "gameController.h"
#include <algorithm>

gravitation::gravitation(textureStateManager & stateObject){
	this->stateInstancePtr = &stateObject;
}

void gravitation::antigravityForce(float strength){
	if(counterForceActive != true){
		this->forceStrength = strength;
		this->playerHeight.clear();
		
		std::fill(this->flatEarthGravity.begin() ,  
				   this->flatEarthGravity.begin() + (gravityValuesCount/2),
				   10 );
		std::fill(this->flatEarthGravity.begin() +(gravityValuesCount/2)+1,  
				   this->flatEarthGravity.end(),
				   -10 );
		// flatEarthGravity[10] camer speed = 0 [... -10, 0, 10  ...]
		for(int x = -10, k=0; k <= gravityValuesCount; x++, k++ )
			if(x == 0)
				playerHeight.push_back( 0 );
			else if (x < 0)
				playerHeight.push_back( gravityEqeuation( x ) );
			else
				playerHeight.push_back(-gravityEqeuation( x ) );
		}	
		// for (auto & v : playerHeight)
		// 	printf("%i \n", v );
		// // exit(1);
}

gravitation::gravityDetails&  gravitation::getHeight(gravitation::gravityDetails& currentVerticalVelocity){
	if(this->counterForceActive == false){
		currentVerticalVelocity.currentPlayerVelocity = 10;
		currentVerticalVelocity.currentCameraVelocity = -10;
		return currentVerticalVelocity;
	}

	if(this->counter < 11)
		this->stateInstancePtr->currentPlayerState = this->stateInstancePtr->jumpDirection;
	else
		this->stateInstancePtr->currentPlayerState = this->stateInstancePtr->landingDirection;

	if( this->counter > 20 ){
		currentVerticalVelocity.currentPlayerVelocity = 10;
		currentVerticalVelocity.currentCameraVelocity = -10;
		return currentVerticalVelocity;
	}
	currentVerticalVelocity.currentPlayerVelocity = -this->flatEarthGravity[this->counter];
	currentVerticalVelocity.currentCameraVelocity = this->flatEarthGravity[this->counter++];
	return currentVerticalVelocity;
}


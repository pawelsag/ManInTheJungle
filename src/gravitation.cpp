#include "gravitation.h"
#include <math.h>
#include "gameController.h"
#include <algorithm>

gravitation::gravitation(textureStateManager & stateObject){
	this->stateInstancePtr = &stateObject;
}

void gravitation::antigravityForce(int strength){
	if(counterForceActive != true){
		this->forceStrength = strength;
		this->playerHeight.clear();
		
		std::fill(this->flatEarthGravity.begin() +1,  
				   this->flatEarthGravity.begin() + (gravityValuesCount/2),
				   10 );
		std::fill(this->flatEarthGravity.begin() +(gravityValuesCount/2)+1,  
				   this->flatEarthGravity.end()-1,
				   -10 );
		// flatEarthGravity[10] camer speed = 0 [... -10, 0, 10  ...]
		for(int x = -10, k=0; k <= gravityValuesCount; x++, k++ )
			playerHeight.push_back( gravityEqeuation( x ) );

	}	
}

gravitation::gravityDetails&  gravitation::getHeight(gravitation::gravityDetails& currentVerticalVelocity){
	if(this->counterForceActive == false){
		currentVerticalVelocity.currentPlayerVelocity = -10;
		currentVerticalVelocity.currentCameraVelocity = 0;
		return currentVerticalVelocity;
	}

	if(this->counter < 11)
		this->stateInstancePtr->currentPlayerState = this->stateInstancePtr->jumpDirection;
	else
		this->stateInstancePtr->currentPlayerState = this->stateInstancePtr->landingDirection;

	if( this->counter > 20 ){
		this->clearJump();
		currentVerticalVelocity.currentPlayerVelocity = 0;
		currentVerticalVelocity.currentCameraVelocity = 0;
		return currentVerticalVelocity;
	}
	currentVerticalVelocity.currentPlayerVelocity = this->playerHeight[this->counter];
	currentVerticalVelocity.currentCameraVelocity = this->flatEarthGravity[this->counter++];
	return currentVerticalVelocity;
}


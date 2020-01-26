#ifndef TEXTURESTATEMANAGER
#define TEXTURESTATEMANAGER
#include "customTypes.h"
class gravitation;
class eventManager;
class textureStateManager
{
private:
	friend class gravitation;
	friend class eventManager;
	ST::CHARACTERSTATE currentPlayerState{ST::CHARACTERSTATE::IDLE};
	ST::CHARACTERSTATE savedPlayerState{ST::CHARACTERSTATE::IDLE};
	ST::CHARACTERSTATE jumpDirection{ST::CHARACTERSTATE::JUMP};
	ST::CHARACTERSTATE landingDirection{ST::CHARACTERSTATE::LANDING};
public:
	textureStateManager()=default;
	~textureStateManager()=default;

	inline void setState(ST::CHARACTERSTATE state){
		if(this->currentPlayerState == ST::CHARACTERSTATE::JUMP &&
		   this->currentPlayerState == ST::CHARACTERSTATE::LANDING){
			return;
		}

	 	if(this->currentPlayerState == ST::CHARACTERSTATE::JUMPLEFT &&
		   this->currentPlayerState == ST::CHARACTERSTATE::LANDINGLEFT ){
	 		return;
	 	}

		this->currentPlayerState = state;
	}

	inline ST::CHARACTERSTATE & getState(){
		return this->currentPlayerState;
	}

	inline void saveCurrentState(){
		this->savedPlayerState = this->currentPlayerState;
	}

	inline void saveState(ST::CHARACTERSTATE state){
		this->savedPlayerState = state;
	}

	inline void restoreState(){
		 this->currentPlayerState = this->savedPlayerState;
	}

	inline void resetState(){
		this->currentPlayerState = ST::CHARACTERSTATE::IDLE;
	}


};

#endif
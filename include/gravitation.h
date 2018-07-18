#ifndef GRAVITATION
#define GRAVITATION
#include <vector>
#include "textureStateManager.h"

class gameController;

constexpr const int gravityValuesCount =20;

class gravitation
{
	friend class gameController; 
	int counter{0};
	int forceStrength{0};
	bool counterForceActive{ false },appActive{true};
	textureStateManager * stateInstancePtr;	
	std::vector<int> height;
public:
	gravitation()=default;
	gravitation(textureStateManager & stateObject);
	~gravitation()=default;
	
	void antigravityForce(int strength);
	int getHeight();
	inline int  gravityEqeuation(int x) {
		return (x-10)*(x+10)*this->forceStrength ;
	}

	inline void activateForce(){
		this->counterForceActive = true;
	}

};

#endif
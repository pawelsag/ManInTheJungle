#ifndef GRAVITATION
#define GRAVITATION
#include <thread>
class gameController;

constexpr const int gravityConstant =-10; 
class gravitation
{
	friend class gameController; 
	int velocity{ gravityConstant };
	int height{0};
	int forceStrength{0};
	bool counterForceActive{ false },appActive{true};
	std::thread gravityThread;
public:
	gravitation();
	~gravitation();
	
	void run();

	inline void antigravityForce(int strength){
		if(counterForceActive != true){
			this->forceStrength = strength;
			counterForceActive = true;
		}
	}
	inline int  gravityEqeuation(int x) {
		return (x-10)*(x+10)*this->forceStrength ;
	}
	inline int getHeight(){
		return this->height +400;
	}
};

#endif
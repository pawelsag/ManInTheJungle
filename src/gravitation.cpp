#include "gravitation.h"
#include <math.h>
#include "gameController.h"

gravitation::gravitation()
:gravityThread(&gravitation::run,this)
{
}

void gravitation::run(){
	int x = -8, x_2 =1;
	while( this->appActive ){

		if(!counterForceActive){
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		this->height = 0;
		x_2 = 1;
		x = -8;
		while( x_2 ){
			x_2 = this->height = this->gravityEqeuation( x );
			x += 1;
			printf("%i\n",this->height  );
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		counterForceActive = false;
	}
	printf("Ending\n");
}

gravitation::~gravitation(){
	gravityThread.join();
}
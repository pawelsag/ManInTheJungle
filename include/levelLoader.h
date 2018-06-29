#include <memory>
#include <fstream>
#include "globalSettings.h"

#ifndef LEVELLOADER
#define LEVELLOADER
using char_ptr = std::unique_ptr<char> ;

class levelLoader
{
	char_ptr levelMapArray;
	size_t size_x, size_y, offset;
	bool levelLoaded;
	std::fstream fileIn;
public:
	levelLoader() =default;
	bool loadLevel(std::string & name);
	~levelLoader();

	inline char_ptr& getLevel(){
		return this->levelMapArray;
	}

private:
	void loadMetaData();
	void loadLevel();
};

#endif
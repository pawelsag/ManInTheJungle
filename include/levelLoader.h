#include <memory>
#include <vector>
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
	std::vector<unsigned char> signatures;
public:
	levelLoader() =default;
	bool loadLevel(const std::string & name);
	~levelLoader(){};

	inline char_ptr& getLevel(){
		return this->levelMapArray;
	}
	inline std::vector<unsigned char> & getSignature(){
		return signatures;
	}

private:
	void loadMetaData();
	void loadLevel();
};

#endif
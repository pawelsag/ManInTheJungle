#include <memory>
#include <vector>
#include <fstream>
#include "globalSettings.h"

#ifndef LEVELLOADER
#define LEVELLOADER

class levelLoader
{
	PType::u_char_ptr levelMapArray;
	size_t size_x, size_y, offset;
	bool levelLoaded;
	std::fstream fileIn;
	std::vector<unsigned char> signatures;
public:
	levelLoader() =default;
	bool loadLevel(const std::string & name);
	~levelLoader(){};

	inline PType::u_char_ptr& getLevel(){
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
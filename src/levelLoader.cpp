#include "levelLoader.h"


bool levelLoader::loadLevel(std::string & name){
	
	fileIn.open(name.c_str(), std::fstream::in | std::fstream::binary);
	// load information about level
	this->loadMetaData();
	try{
		// create new map for given level information
		this->levelMapArray = char_ptr(new char[ this->size_x * this->size_y ]);
	}catch(std::bad_alloc &ba){
		printf("Error : %s", ba.what() );
		return false;
	}
	this->loadLevel();

	fileIn.close();

	return true;
}

void levelLoader::loadMetaData(){
	
	fileIn.read((char*)&this->size_x, 4 );
	fileIn.read((char*)&this->size_y, 4 );
	fileIn.read((char*)&this->offset, 2 );
	printf("%i %i %i \n", size_x, size_y, offset);
}
void levelLoader::loadLevel(){
	fileIn.seekg( 0, fileIn.end );
	size_t fileSize = fileIn.tellg();
	fileSize -= offset;

	fileIn.seekg( offset, fileIn.beg );

	fileIn.read(this->levelMapArray.get(),fileSize);

}

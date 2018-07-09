#include "levelLoader.h"


bool levelLoader::loadLevel(const std::string & name){
	
	fileIn.open( (pathToLevels + name).c_str(), std::fstream::in | std::fstream::binary);
	printf("%s\n", (pathToLevels + name).c_str());
	if( !fileIn.is_open() ){
		printf("Can't load map \n");
		exit(1);
	}
	// load information about level
	this->loadMetaData();
	try{
		// create new map for given level information
		this->levelMapArray = PType::u_char_ptr(new unsigned char[ this->size_x * this->size_y ]);
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
	
	unsigned char signature = 0;
	/// substract from offset 0xA to get size of textures signature /// 
	/// read signatures which represnts pixel in given tilset ///  
	for(size_t i =0 ; i < offset - 0xA ; i++){
		fileIn.read((char*)&signature , 1);

		signatures.push_back(signature);	
	}
	printf("%i %i %i \n", size_x, size_y, offset);
}

void levelLoader::loadLevel(){
	fileIn.seekg( 0, fileIn.end );
	size_t fileSize = fileIn.tellg();
	fileSize -= offset;

	fileIn.seekg( offset, fileIn.beg );

	fileIn.read((char*)this->levelMapArray.get(),fileSize);
	
}

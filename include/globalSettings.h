#ifndef GLOBALSETTINGS
#define GLOBALSETTINGS
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr int  JUNGLE_TILE_X_SIZE = SCREEN_WIDTH /20;
constexpr int  JUNGLE_TILE_Y_SIZE = SCREEN_HEIGHT/15; 
constexpr const char * pathToBG = "./Textures/background/";
constexpr const char * pathToCharacter = "./Textures/Character/sprites/";
constexpr const char * pathToJungleTiles = "./Textures/jungle_tileset/";
constexpr const int velocity = 5; 
const std::string pathToLevels = "./config/levels/"; 
constexpr const char * levels[2] = { "level1raw.bin" /*,"LEVEL2"*/ };
constexpr const char * charcterStateNames[7] = {
										"main-idle.png", "main-jump.png" , "main-run-left.png"
									 	,"main-run-right.png" , "main-hang.png" , "main-special.png"
									 	,"main-landing.png"
									 };

namespace PType
{
	using char_ptr = std::unique_ptr<char[]> ;
	using u_char_ptr = std::unique_ptr<unsigned char[]> ;
	using TextureVector = std::vector< SDL_Texture *>;
	using RectPtr = std::unique_ptr<SDL_Rect>;

	using RectVector = std::vector<SDL_Rect >;
	using TextureVector_Ptr = std::shared_ptr<TextureVector>;
}

#endif
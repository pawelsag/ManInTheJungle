#ifndef GLOBALSETTINGS
#define GLOBALSETTINGS
 
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr const char * pathToBG = "C:/SDLPRojects/SDL GAME/Textures/background/";
constexpr const char * pathToCharacter = "C:/SDLPRojects/SDL GAME/Textures/Chacter_with_outline/sprites";
constexpr const char * pathToJungleTiles = "C:/SDLPRojects/SDL GAME/Textures/Chacter_with_outline/jungle_tileset";
constexpr const float velocity = 12.0; 
//move it letter to game logic class 
static int globalCameraVelocity = 0;

constexpr const char * levels[2] = {"LEVEL1","LEVEL2"};

enum STATES{
	ACTIVE,
	QUIT
};
enum TEXTURETYPE{
	BACKGROUND,
	CHARACTER,
	BOT,
	OBSTACLE
};

#endif
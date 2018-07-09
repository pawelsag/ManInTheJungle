#ifdef _WIN32
#include <windows.h>
#endif
#include "gameController.h"
#include <stdio.h>

#ifdef _WIN32

int CALLBACK WinMain(
  _In_ HINSTANCE hInstance,
  _In_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
  )
{
	gameController mainGame;
	mainGame.run();
	return 0;
}
#endif
int main(int argc, char const *argv[])
{
	
	gameController mainGame;
	mainGame.run();

	return 0;
}
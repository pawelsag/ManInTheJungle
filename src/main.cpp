#include <windows.h>
#include "gameController.h"
#include <stdio.h>
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

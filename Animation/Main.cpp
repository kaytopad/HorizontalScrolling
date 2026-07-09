#include "Dxlib.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	
	ChangeWindowMode(TRUE);
	SetWindowSize(Config::WINDOW_WIDTH,Config::WINDOW_HEIGHT);
	// Initialize DxLib
	if (DxLib_Init() == -1) { return -1;}
	SetDrawScreen(DX_SCREEN_BACK);

	Game game;

	game.Init();

	// Main loop
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		// Clear the screen
		ClearDrawScreen();
		game.Update();
		game.Draw();

		ScreenFlip();
	}
	// Cleanup and exit
	DxLib_End();
	return 0;
}
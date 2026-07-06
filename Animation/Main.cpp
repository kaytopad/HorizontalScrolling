#include "Dxlib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Initialize DxLib
	if (DxLib_Init() == -1) { return -1;}
	// Main loop
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		// Clear the screen
		ClearDrawScreen();
		SetFontSize(30);
		DrawFormatString(77, 250, GetColor(255, 100, 0), "Just Do It!");
		// Update the screen
		ScreenFlip();
	}
	// Cleanup and exit
	DxLib_End();
	return 0;
}
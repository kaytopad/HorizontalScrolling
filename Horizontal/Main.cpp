#include "DxLib.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Initialize DxLib
	if (DxLib_Init() == -1) {
		return -1; // Initialization failed
	}
	// Set the window title
	// Main loop
	while (ProcessMessage() == 0) {
		// Clear the screen
		ClearDrawScreen();
		// Draw something (e.g., a rectangle)
		DrawBox(100, 100, 200, 200, GetColor(255, 0, 0), TRUE);
		// Update the screen
		ScreenFlip();
	}
	// Cleanup and exit
	DxLib_End();
	return 0;
}
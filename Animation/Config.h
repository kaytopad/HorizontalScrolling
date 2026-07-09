#pragma once

namespace Config
{
	//===============================
	// Window settings
	//===============================
	constexpr int WINDOW_WIDTH = 1920;
	constexpr int WINDOW_HEIGHT = 1080;

	constexpr int PLAYER_DRAW_X = 198;
	constexpr int PLAYER_DRAW_Y = 198;

	//===============================
	// Player settings
	//===============================

	//1コマのサイズ
	constexpr int PLAYER_WIDTH = 210;
	constexpr int PLAYER_HEIGHT = 220;
	//分割数
	constexpr int PLAYER_COL = 7;
	constexpr int PLAYER_ROW = 4;

	//総フレーム数
	constexpr int PLAYER_TOTAL_FRAMES = PLAYER_COL * PLAYER_ROW;

	//===============================
	// アニメーション速度
	//===============================
	constexpr int IDLE_SPEED = 10;
	constexpr int WALK_SPEED = 9;
	constexpr int RUN_SPEED = 10;
	constexpr int JUMP_SPEED = 6;

}
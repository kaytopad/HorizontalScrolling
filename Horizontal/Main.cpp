#include "DxLib.h"
#include "Game.h"
#include "Config.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	//-----------------------------------------
	// ウィンドウモードに設定
	//-----------------------------------------
	ChangeWindowMode(TRUE);
	// ウィンドウサイズを設定
	SetWindowSize(GameConst::SCREEN_WIDTH, GameConst::SCREEN_HEIGHT);
	//-----------------------------------------
	// DXライブラリ初期化
	//-----------------------------------------
	if (DxLib_Init() == -1){ return -1;}
	// 描画先を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);
	// 文字フォントを設定
	SetFontSize(20);

	// ゲームクラス生成
	Game game;
	// ゲーム初期化
	game.Init();
	//-----------------------------------------
	// メインループ
	//-----------------------------------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ゲーム更新
		game.Update();
		// 画面クリア
		ClearDrawScreen();
		// ゲーム描画
		game.Draw();
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}
	// DXライブラリ終了処理
	DxLib_End();
	// 正常終了
	return 0;
}
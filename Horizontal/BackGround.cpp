#include "Background.h"
#include "DxLib.h"

//=====================================================
// 初期化
//=====================================================
void Background::Init()
{
	imageHandle = LoadGraph("img/Background.png");
}

//=====================================================
// 描画
//=====================================================
void Background::Draw(float cameraX)
{
	DrawGraph(-(int)(cameraX * 0.5f),0,imageHandle,TRUE);
}
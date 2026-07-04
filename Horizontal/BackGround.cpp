#include "Background.h"
#include "DxLib.h"

//=====================================================
// èâä˙âª
//=====================================================
void Background::Init()
{
	imageHandle = LoadGraph("img/Background.png");
}

//=====================================================
// ï`âÊ
//=====================================================
void Background::Draw(float cameraX)
{
	DrawGraph(-(int)(cameraX * 0.5f),0,imageHandle,TRUE);
}
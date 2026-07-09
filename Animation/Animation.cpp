#include "Animation.h"

//===============================
// コンストラクタ
//===============================
Animation::Animation()
{
	images = nullptr;
	startFrame = 0;
	frameCount = 1;
	speed = 10;
	startTime = 0;
}
//===============================
// 分割画像設定
//===============================
void Animation::SetImages(int* img)
{
	images = img;
}

//===============================
// アニメーション再生
//===============================
void Animation::Play(int start, int frame, int spd)
{
	startFrame = start;
	frameCount = frame;
	speed = spd;
}

//===============================
// 現在描画する画像取得
//===============================
int Animation::GetImage(int currentTime)
{

	//===============================
	//アニメーション番号計算
	//===============================
	int fram = (currentTime / speed) % frameCount;
	return images[startFrame + fram];
}
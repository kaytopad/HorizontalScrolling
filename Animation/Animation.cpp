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
void Animation::Play(int start, int frame, int spd, int currentTime)
{
	startFrame = start;
	frameCount = frame;
	speed = spd;
	startTime = currentTime;
}

//===============================
// 現在描画する画像取得
//===============================
int Animation::GetImage(int currentTime)
{
	//===============================
	// 経過時間を計算
	//===============================
	int elapsedTime = currentTime - startTime;

	//===============================
	//アニメーション番号計算
	//===============================
	int fram = (elapsedTime / speed) % frameCount;
	return images[startFrame + fram];
}
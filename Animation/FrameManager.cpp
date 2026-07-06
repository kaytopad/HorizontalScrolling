#include "FrameManager.h"

//===============================
// コンストラクタ
//===============================
FrameManager::FrameManager()
{
	// フレームカウンターを初期化
	frameCounter = 0;
}
//===============================
// 更新
//===============================
void FrameManager::Update()
{
	// フレームカウンターを更新
	frameCounter++;
}

//===============================
// 現在フレーム取得
//===============================
int FrameManager::GetFrameCounter() const
{
	// フレームカウンターを返す
	return frameCounter;
}
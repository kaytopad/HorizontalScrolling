#pragma once

#include "Config.h"
#include "Animation.h"
#include "AnimationType.h"
#include "FrameManager.h"

class Game
{
private:
	//===============================
	// フレームマネージャー
	//===============================
	FrameManager frameManager;
	//===============================
	// アニメーション
	//===============================
	Animation animations;
	//===============================
	// 分割画像
	//===============================
	int images[Config::PLAYER_TOTAL_FRAMES];
	//===============================
	// 現在のアニメーション
	//===============================
	AnimationType currentAnim;
	//===============================
	// 前回のスペースキーの状態
	//===============================
	bool oldSpace;
	//===============================
	// アニメーション切替
	//===============================
	void PlayerAnimation(AnimationType type);

public:
	void Init();
	void Update();
	void Draw();

};

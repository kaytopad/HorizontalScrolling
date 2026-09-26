#pragma once

#include "Collision.h"

class Player
{
private:
	//プレイヤーの位置
	float x;
	float y;

	//プレイヤーの移動速度
	float velocityX;
	float velocityY;

	//ジャンプフラグ
	bool isJumping;

	//プレイヤーの当たり判定
	Collision collision;

	//足元の当たり判定
	Collision footCollision;

	//頭の当たり判定
	Collision headCollision;

public:
	Player();
	~Player();
	//初期化
	//更新
	//描画

	//マップとの衝突処理

	//Collisoｎの取得

	//座標



};


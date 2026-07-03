#pragma once

class WorldObject
{
private:
	// The x position of the object in the world
	float worldX;
	float worldY;
public:
	//=====================================================
	// コンストラクタ
	//=====================================================
	WorldObject(float worldX,float worldY);
	//=====================================================
	// 描画
	//=====================================================
	void Draw(float cameraX);

};
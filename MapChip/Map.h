#pragma once

#include <vector>
#include <string>


class Map
{
private:
	//マップチップの番号
	std::vector<std::vector<int>> mapData;
	//当たり判定の情報
	std::vector<std::vector<int>> hitData;

	//マップチップ画像
	int chipImage[64];

	//マップの縦横のマスの数
	int mapWidth;
	int mapHeight;

	//マップの大きさ
	static constexpr int CHIP_SIZE = 64;

	//csvファイルの読み込み
	bool LoadCSV(const char* fileName, std::vector < std::vector<int >> &data);
public:
	/// <summary>
	/// Mapコンストラクタ
	/// </summary>
	Map();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>読み込み不正</returns>
	bool Init();

	/// <summary>
	/// マップの描画
	/// </summary>
	/// <param name="cameraX">カメラ座標X</param>
	/// <param name="cameraY">カメラ座標Y</param>
	void Draw(float cameraX,float cameraY);
	
	/// <summary>
	/// 通行できるかどうか
	/// </summary>
	/// <param name="tileX">タイルX座標</param>
	/// <param name="tileY">タイルY座標</param>
	/// <returns>通過可能判定</returns>
	bool IsSolid(int tileX,int tileY) const;

	/// <summary>
	/// ワールド座標から当たり判定を調べる
	/// </summary>
	/// <param name="worldX">ワールド座標X</param>
	/// <param name="worldY">ワールド座標Y</param>
	/// <returns>ワールド座標当たり判定</returns>
	bool IsSolidAt(float worldX,float worldY) const;

};


#include "Map.h"
#include "Dxlib.h"

#include <fstream>
#include <sstream>
#include<cmath>
using namespace std;
//コンストラクタ
Map::Map()
{
	mapWidth = 0;
	mapHeight = 0;
	for (int i = 0; i < 64; i++)
	{
		chipImage[i] = -1;
	}
}

bool Map::LoadCSV(const char* fileName, vector < vector<int >>& data)
{
	ifstream file(fileName);

	if (!file.is_open())
	{
		return false;
	}
	data.clear();

	string line;

	while (getline(file,line))
	{
		vector<int> row;
		stringstream ss(line);
		string value;

		while (getline(ss, value, ','))
		{
			if (value.empty())
			{
				return false;
			}

			try
			{
				row.push_back(stoi(value));
			}
			catch (const std::exception&)
			{
				return false;
			}

		}

		if (!row.empty())
		{
			data.push_back(row);
		}
	}

		// すべての行の列数が同じか確認

	const size_t width = data[0].size();
	for (const auto& row : data)
	{
		if (row.size() != width)
		{
			return false;
		}
	}

	return true;
}


bool Map::Init()
{
	// 描画用マップを読み込む
	if (!LoadCSV("data/Map.csv", mapData)){
		printfDx("Map.csv の読み込みに失敗\n");
		return false; }

	// 当たり判定用マップを読み込む
	if (!LoadCSV("data/Hit.csv", hitData)){
		printfDx("Map.csv の読み込みに失敗\n");
		return false; }

	// 2つのCSVのサイズを確認
	if (mapData.size() != hitData.size() || mapData[0].size() != hitData[0].size())
	{
		return false;
	}

	mapHeight = static_cast<int>(mapData.size());
	mapWidth = static_cast<int>(mapData[0].size());

	// マップチップ画像を64枚に分割して読み込む
	if (LoadDivGraph("data/MapChip.png",64,16,4,CHIP_SIZE,CHIP_SIZE,chipImage) == -1)
	{
		return false;
	}

	return true;
}

// マップ描画
void Map::Draw(float cameraX, float cameraY)
{
	for (int y = 0; y < mapHeight; y++)
	{
		for (int x = 0; x < mapWidth; x++)
		{
			int chipNo = mapData[y][x];

			// -1なら描画しない
			if (chipNo == -1)
			{
				continue;
			}

			// 存在する画像番号か確認
			if (chipNo < 0 || chipNo >= 64)
			{
				continue;
			}

			// マップのワールド座標
			int worldX = x * CHIP_SIZE;
			int worldY = y * CHIP_SIZE;

			// ワールド座標から画面座標へ変換
			int screenX =
				worldX - static_cast<int>(cameraX);

			int screenY =
				worldY - static_cast<int>(cameraY);

			// マップチップを描画
			DrawGraph(screenX,screenY,chipImage[chipNo],TRUE);
		}
	}
}

// 指定したマスが通行できない地形か調べる
bool Map::IsSolid(int tileX, int tileY) const
{
	// マップ外は壁として扱う
	if (tileX < 0 || tileX >= mapWidth ||
		tileY < 0 || tileY >= mapHeight)
	{
		return true;
	}

	// 1なら床や壁などの障害物
	return hitData[tileY][tileX] == 1;
}

// ワールド座標から地形を調べる
bool Map::IsSolidAt(float worldX,float worldY) const
{
	int tileX = static_cast<int>(std::floor(worldX / CHIP_SIZE));

	int tileY = static_cast<int>(std::floor(worldY / CHIP_SIZE));

	return IsSolid(tileX, tileY);
}
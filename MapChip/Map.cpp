#include "Map.h"

#include "DxLib.h"

#include <fstream>
#include <sstream>
#include <string>

Map::Map(): mapXNum(0),mapYNum(0),isInitialized(false)
{
    for (int i = 0; i < Config::MAP_CHIP_IMAGE_COUNT; ++i)
    {
        chipImages[i] = -1;
    }
}

Map::~Map()
{
    // DxLib_End()より前にFinalize()を呼ぶ設計にしてください。
    Finalize();
}

bool Map::Init()
{
    Finalize();

    // 画像をチップ単位に分割して読み込む
    if (LoadDivGraph(
        Config::MAP_CHIP_IMAGE_PATH,
        Config::MAP_CHIP_IMAGE_COUNT,
        Config::MAP_CHIP_IMAGE_COLUMNS,
        Config::MAP_CHIP_IMAGE_ROWS,
        Config::MAP_CHIP_SIZE,
        Config::MAP_CHIP_SIZE,
        chipImages) == -1)
    {
        Finalize();
        return false;
    }

    // CSVファイルを読み込む
    if (!LoadMap(Config::MAP_HIT_CSV_PATH, hitMap) ||
        !LoadMap(Config::MAP_BACK_CSV_PATH, backMap) ||
        !LoadMap(Config::MAP_BASE_CSV_PATH, baseMap) ||
        !LoadMap(Config::MAP_NEAR_CSV_PATH, nearMap))
    {
        Finalize();
        return false;
    }

    mapYNum = static_cast<int>(hitMap.size());

    if (mapYNum == 0)
    {
        Finalize();
        return false;
    }

    mapXNum = static_cast<int>(hitMap[0].size());

    // 描画用レイヤーのサイズが当たり判定用レイヤーと一致するか確認する
    const std::vector<std::vector<int>>* maps[] =
    {
        &backMap,
        &baseMap,
        &nearMap
    };

    for (int i = 0; i < 3; ++i)
    {
        if (static_cast<int>(maps[i]->size()) != mapYNum)
        {
            Finalize();
            return false;
        }

        for (int y = 0; y < mapYNum; ++y)
        {
            if (static_cast<int>((*maps[i])[y].size()) != mapXNum)
            {
                Finalize();
                return false;
            }
        }
    }

    isInitialized = true;
    return true;
}

bool Map::LoadMap(
    const char* filePath,
    std::vector<std::vector<int>>& mapData)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return false;
    }

    mapData.clear();

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::vector<int> row;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {
            std::stringstream cellStream(cell);
            int value = Config::MAP_EMPTY;

            if (!(cellStream >> value))
            {
                return false;
            }

            row.push_back(value);
        }

        if (row.empty())
        {
            return false;
        }

        // CSVの各行の横幅が同じであることを確認する
        if (!mapData.empty() && row.size() != mapData[0].size())
        {
            return false;
        }

        mapData.push_back(row);
    }

    return !mapData.empty();
}

void Map::Draw() const
{
    if (!isInitialized)
    {
        return;
    }

    // 描画順：奥の背景 → 地面 → 手前
    DrawLayer(backMap);
    DrawLayer(baseMap);
    DrawLayer(nearMap);
}

void Map::DrawLayer(const std::vector<std::vector<int>>& mapData) const
{
    for (int y = 0; y < static_cast<int>(mapData.size()); ++y)
    {
        for (int x = 0; x < static_cast<int>(mapData[y].size()); ++x)
        {
            const int chipNumber = mapData[y][x];

            if (chipNumber == Config::MAP_EMPTY)
            {
                continue;
            }

            // CSVのチップ番号は1始まり、画像配列の番号は0始まり
            const int chipIndex = chipNumber - 1;

            if (chipIndex < 0 ||
                chipIndex >= Config::MAP_CHIP_IMAGE_COUNT)
            {
                continue;
            }

            const int drawX =
                Config::MAP_DRAW_ORIGIN_X + x * Config::MAP_CHIP_SIZE;
            const int drawY =
                Config::MAP_DRAW_ORIGIN_Y + y * Config::MAP_CHIP_SIZE;

            DrawGraph(drawX, drawY, chipImages[chipIndex], TRUE);
        }
    }
}

void Map::HitCalc(Collision& checkRect) const
{
    if (!isInitialized)
    {
        return;
    }

    for (int y = 0; y < mapYNum; ++y)
    {
        for (int x = 0; x < mapXNum; ++x)
        {
            if (hitMap[y][x] == Config::MAP_EMPTY)
            {
                continue;
            }

            Collision blockRect;
            blockRect.SetRect(
                Config::MAP_DRAW_ORIGIN_X + x * Config::MAP_CHIP_SIZE,
                Config::MAP_DRAW_ORIGIN_Y + y * Config::MAP_CHIP_SIZE,
                Config::MAP_CHIP_SIZE,
                Config::MAP_CHIP_SIZE);

            if (checkRect.IsHit(blockRect))
            {
                checkRect.FixPosition(blockRect, GetBlockInfo(x, y));
            }
        }
    }
}

int Map::GetBlockType(int mapX, int mapY) const
{
    if (!IsValidMapPosition(mapX, mapY))
    {
        return Config::MAP_EMPTY;
    }

    return hitMap[mapY][mapX];
}

unsigned char Map::GetBlockInfo(int mapX, int mapY) const
{
    unsigned char blockInfo = 0;

    if (GetBlockType(mapX - 1, mapY) == Config::MAP_EMPTY)
    {
        blockInfo |= Config::BLOCK_LEFT;
    }

    if (GetBlockType(mapX + 1, mapY) == Config::MAP_EMPTY)
    {
        blockInfo |= Config::BLOCK_RIGHT;
    }

    if (GetBlockType(mapX, mapY - 1) == Config::MAP_EMPTY)
    {
        blockInfo |= Config::BLOCK_UP;
    }

    if (GetBlockType(mapX, mapY + 1) == Config::MAP_EMPTY)
    {
        blockInfo |= Config::BLOCK_DOWN;
    }

    return blockInfo;
}

bool Map::IsValidMapPosition(int mapX, int mapY) const
{
    if (mapX < 0 || mapY < 0)
    {
        return false;
    }

    if (mapY >= static_cast<int>(hitMap.size()))
    {
        return false;
    }

    if (mapX >= static_cast<int>(hitMap[mapY].size()))
    {
        return false;
    }

    return true;
}

void Map::Finalize()
{
    for (int i = 0; i < Config::MAP_CHIP_IMAGE_COUNT; ++i)
    {
        if (chipImages[i] != -1)
        {
            DeleteGraph(chipImages[i]);
            chipImages[i] = -1;
        }
    }

    hitMap.clear();
    backMap.clear();
    baseMap.clear();
    nearMap.clear();

    mapXNum = 0;
    mapYNum = 0;
    isInitialized = false;
}

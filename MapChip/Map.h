#pragma once

#include <vector>

#include "Collision.h"
#include "Config.h"

// マップの読み込み・描画・マップに対する当たり判定を管理するクラス
class Map
{
public:
    Map();
    ~Map();

    // 画像とCSVを読み込む
    bool Init();

    // マップを奥から手前の順に描画する
    void Draw() const;

    // Collision矩形をマップに合わせて押し戻す
    void HitCalc(Collision& checkRect) const;

    // 指定したマップ座標の当たり判定チップ番号を取得する
    int GetBlockType(int mapX, int mapY) const;

    // 指定チップの上下左右に空きがある方向を取得する
    unsigned char GetBlockInfo(int mapX, int mapY) const;

    // DxLib終了前に呼び出して、画像などを解放する
    void Finalize();

private:
    bool LoadMap(
        const char* filePath,
        std::vector<std::vector<int>>& mapData);

    void DrawLayer(const std::vector<std::vector<int>>& mapData) const;

    bool IsValidMapPosition(int mapX, int mapY) const;

    int chipImages[Config::MAP_CHIP_IMAGE_COUNT];

    std::vector<std::vector<int>> hitMap;
    std::vector<std::vector<int>> backMap;
    std::vector<std::vector<int>> baseMap;
    std::vector<std::vector<int>> nearMap;

    int mapXNum;
    int mapYNum;
    bool isInitialized;
};

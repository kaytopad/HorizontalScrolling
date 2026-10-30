#pragma once

#include "Config.h"

// 当たり判定用の矩形と、矩形の衝突処理を管理するクラス。
// 構造体は使用せず、矩形の情報をCollisionクラスで管理します。
class Collision
{
public:
    Collision();

    // 矩形の位置と大きさを設定する
    void SetRect(int x, int y, int width, int height);

    // 矩形の位置だけを変更する
    void SetPosition(int x, int y);

    // 矩形同士が重なっているか調べる
    bool IsHit(const Collision& other) const;

    // 衝突した矩形を、指定された空き方向へ押し戻す
    void FixPosition(
        const Collision& block,
        unsigned char blockInfo);

    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetRight() const;
    int GetBottom() const;

private:
    int x;
    int y;
    int width;
    int height;
};

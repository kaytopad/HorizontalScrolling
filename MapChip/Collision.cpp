#include "Collision.h"

#include <cstdlib>
#include <limits>

Collision::Collision()
    : x(0),
      y(0),
      width(0),
      height(0)
{
}

void Collision::SetRect(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Collision::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

bool Collision::IsHit(const Collision& other) const
{
    // 右端・下端が接しているだけなら、重なっていないものとする
    if (GetRight() <= other.GetX())
    {
        return false;
    }

    if (GetX() >= other.GetRight())
    {
        return false;
    }

    if (GetBottom() <= other.GetY())
    {
        return false;
    }

    if (GetY() >= other.GetBottom())
    {
        return false;
    }

    return true;
}

void Collision::FixPosition(
    const Collision& block,
    unsigned char blockInfo)
{
    if (!IsHit(block))
    {
        return;
    }

    // それぞれの方向へ押し戻すために必要な移動量を計算する
    int moveLeft = block.GetX() - GetRight();
    int moveRight = block.GetRight() - GetX();
    int moveUp = block.GetY() - GetBottom();
    int moveDown = block.GetBottom() - GetY();

    // 隣が空いていない方向は、押し戻し候補から外す
    const int unavailable = std::numeric_limits<int>::max();

    if ((blockInfo & Config::BLOCK_LEFT) == 0)
    {
        moveLeft = unavailable;
    }

    if ((blockInfo & Config::BLOCK_RIGHT) == 0)
    {
        moveRight = unavailable;
    }

    if ((blockInfo & Config::BLOCK_UP) == 0)
    {
        moveUp = unavailable;
    }

    if ((blockInfo & Config::BLOCK_DOWN) == 0)
    {
        moveDown = unavailable;
    }

    // 有効な候補の中から、移動量が最も小さい方向を選ぶ
    int bestMove = unavailable;
    int direction = -1;

    if (moveLeft != unavailable && std::abs(moveLeft) < bestMove)
    {
        bestMove = std::abs(moveLeft);
        direction = 0;
    }

    if (moveRight != unavailable && std::abs(moveRight) < bestMove)
    {
        bestMove = std::abs(moveRight);
        direction = 1;
    }

    if (moveUp != unavailable && std::abs(moveUp) < bestMove)
    {
        bestMove = std::abs(moveUp);
        direction = 2;
    }

    if (moveDown != unavailable && std::abs(moveDown) < bestMove)
    {
        bestMove = std::abs(moveDown);
        direction = 3;
    }

    // 選んだ方向へ矩形を移動させ、ブロックとの重なりを解消する
    switch (direction)
    {
    case 0:
        x = block.GetX() - width;
        break;

    case 1:
        x = block.GetRight();
        break;

    case 2:
        y = block.GetY() - height;
        break;

    case 3:
        y = block.GetBottom();
        break;

    default:
        // 周囲に空き方向がない場合は、ここでは押し戻せない
        break;
    }
}

int Collision::GetX() const
{
    return x;
}

int Collision::GetY() const
{
    return y;
}

int Collision::GetWidth() const
{
    return width;
}

int Collision::GetHeight() const
{
    return height;
}

int Collision::GetRight() const
{
    return x + width;
}

int Collision::GetBottom() const
{
    return y + height;
}

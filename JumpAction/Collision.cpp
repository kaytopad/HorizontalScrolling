#include "Collision.h"
#include "DxLib.h"

#include <cmath>


void Collision::Init(float width, float height)
{
    this->width = width;
    this->height = height;

    left = 0.0f;
    top = 0.0f;
    right = width;
    bottom = height;
}


void Collision::SetPosition(float x, float y)
{
    left = x;
    top = y;

    right = x + width;
    bottom = y + height;
}


bool Collision::IsHit(const Collision& other) const
{
    return
        left < other.right &&
        other.left < right &&
        top < other.bottom &&
        other.top < bottom;
}


void Collision::FixPosition(const Collision& other)
{
    float leftPush = other.left - right;
    float rightPush = other.right - left;

    float topPush = other.top - bottom;
    float bottomPush = other.bottom - top;


    float pushX = std::fabs(leftPush) < std::fabs(rightPush)? leftPush: rightPush;

    float pushY = std::fabs(topPush) < std::fabs(bottomPush)? topPush: bottomPush;


    if (std::fabs(pushX) < std::fabs(pushY))
    {
        left += pushX;
        right += pushX;
    }
    else
    {
        top += pushY;
        bottom += pushY;
    }
}


void Collision::Draw() const
{
    DrawBox(static_cast<int>(left),static_cast<int>(top),static_cast<int>(right),static_cast<int>(bottom),GetColor(255, 0, 0),
        FALSE);
}
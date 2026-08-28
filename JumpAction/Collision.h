#pragma once

class Collision
{
private:

    float width;
    float height;

    float left;
    float top;
    float right;
    float bottom;


public:

    void Init(float width, float height);

    void SetPosition(float x, float y);

    bool IsHit(const Collision& other) const;

    void FixPosition(const Collision& other);

    void Draw() const;

    float GetLeft() const { return left; }
    float GetTop() const { return top; }
};
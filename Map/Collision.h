#pragma once


class Collision
{
public:

    /// <summary>
    /// 矩形同士が衝突しているか調べる
    /// </summary>
    static bool IsHitRect(float left1,float top1,float right1,float bottom1,
        float left2,float top2,float right2,float bottom2);
};
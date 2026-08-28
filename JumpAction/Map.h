#pragma once

#include "Collision.h"

class Map
{
private:

    int mapChipImg[2];


public:

    void Init();

    void Draw();

    void Finalize();

    bool CheckCollision(Collision& collision);
};
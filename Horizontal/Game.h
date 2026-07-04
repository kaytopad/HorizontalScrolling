#pragma once

#include <vector>

#include "Camera.h"
#include "Background.h"
#include "Map.h"

class Game
{
private:

	Camera camera;

	Background background;

	std::vector<Map> objects;
public:

	void Init();

	void Update();

	void Draw();

};
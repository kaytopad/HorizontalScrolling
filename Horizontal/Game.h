#pragma once

#include <vector>

#include "Camera.h"
#include "Background.h"
#include "WorldObject.h"

class Game
{
private:

	Camera camera;

	Background background;

	std::vector<WorldObject> objects;
public:

	void Init();

	void Update();

	void Draw();

};
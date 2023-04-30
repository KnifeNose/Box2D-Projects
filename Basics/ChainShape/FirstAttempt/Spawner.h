#pragma once

#include <vector>
#include "Circle.h"

class Spawner
{
public:

	Spawner(b2World* world);

	void setup(float x, float y);

	void update();

	float posX;
	float posY;

	std::vector<float> rad;

	std::vector<Circle> circs;

	b2World* mWorld;

	int count;
};

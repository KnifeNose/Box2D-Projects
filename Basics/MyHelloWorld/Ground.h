#pragma once

#include <utility>
#include <box2d/box2d.h>

class Ground
{
public:
	Ground(b2World* world);

	Ground(b2World* world, float width, float height, float x, float y);

	void setup();

	void draw();

	std::pair<float, float> pos;
	
	float hheight;
	float wwidth;
	
	b2World* mWorld;

	b2Body* gBody;
};


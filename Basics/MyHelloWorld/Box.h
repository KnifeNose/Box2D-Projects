#pragma once

#include <vector>
#include <box2d/box2d.h>

class Box
{
public:
	Box(b2World* world);

	void setup(float x, float y);

	void draw();

	bool firstFrame;

	float height;
	
	float width;

private:

	std::pair<float, float> pos;

	float density;


	b2World* mWorld;

	b2Body* body;
};

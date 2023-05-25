#pragma once
#include <utility>
#include <box2d/box2d.h>

class Box
{
public:
	Box(b2World* world);

	void setup(float x, float y);

	void drawRect();

	bool firstFrame;


private:
	std::pair<float, float> pos;

	b2World* mWorld;
	b2Body* body;
};


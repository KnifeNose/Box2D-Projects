#pragma once

#include <box2d/box2d.h>
#include <GLFW/glfw3.h>

class Circle
{
public:
	Circle(b2World* world);

	void setup(float x, float y);

	void draw();

	b2World* mWorld;

	b2Body* body;

	float radius;

	bool firstFrame;
};

#include "Box.h"
#include <random>
#include <box2d/box2d.h>
#include <GLFW/glfw3.h>
#include <iostream>

Box::Box(b2World* world)
	:mWorld(world), body(), firstFrame(true)
{
	pos.first = 0;
	pos.second = 0;

	width = 1;
	height = 1;

	density = (width + height) / 2;
}

void Box::setup(float x, float y)
{
	pos.first = x;
	pos.second = y;

	density = (width + height) / 2;

	// Create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.first, pos.second);
	body = mWorld->CreateBody(&bodyDef);

	// Create shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(width, height);

	// Create Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	firstFrame = false;
}

void Box::draw()
{
	b2Vec2 position = body->GetPosition();
	float angle = body->GetAngle();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(angle * 180.0f / b2_pi, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex2f(-width, -height);
	glVertex2f(width, -height);
	glVertex2f(width, height);
	glVertex2f(-width, height);
	glEnd();
	glPopMatrix();
	//std::cout << height << ' ' << width << std::endl;
}

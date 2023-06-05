#include "Ground.h"
#include <box2d/box2d.h>
#include <GLFW/glfw3.h>

Ground::Ground(b2World* world) 
: mWorld(world), gBody()
{
	wwidth = 0;
	hheight = 0;

	pos.first = 0;
	pos.second = 0;
}

Ground::Ground(b2World* world, float width, float height, float x, float y)
	:mWorld(world), gBody()
{
	wwidth = width;
	hheight = height;

	pos.first = x;
	pos.second = y;
}

void Ground::setup()
{
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(pos.first, pos.second);
	gBody = mWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(wwidth, hheight);

	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &groundBox;
	groundFixtureDef.friction = 0.5f;
	groundFixtureDef.restitution = 0.0f;
	groundFixtureDef.density = 0.0f;

	gBody->CreateFixture(&groundFixtureDef);
}

void Ground::draw()
{
	b2Vec2 position = gBody->GetPosition();
	float angle = gBody->GetAngle();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(angle * 180.0f / b2_pi, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.7f, 0.3f);
	glVertex2f(-wwidth, -hheight);
	glVertex2f(wwidth, -hheight);
	glVertex2f(wwidth, hheight);
	glVertex2f(-wwidth, hheight);
	glEnd();
	glPopMatrix();
}

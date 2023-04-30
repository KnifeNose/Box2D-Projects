#include "Circle.h"
#include <GLFW/glfw3.h>
#include <box2d/box2d.h>
#include <cmath>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dis(0.1f, 1.0f);

Circle::Circle(b2World* world)
	:mWorld(world), body(nullptr), radius(0.5f), firstFrame(true)
{
}

void Circle::setup(float x, float y)
{
	this->radius = dis(gen);
	
	// Create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);
	body = mWorld->CreateBody(&bodyDef);
	
	// Create shape
	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = radius;

	// Create fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	firstFrame = false;
	
}

void Circle::draw()
{
	b2Vec2 position = body->GetPosition();
	float angle = body->GetAngle();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0.0f);
	glRotatef(angle * 180.0f / b2_pi, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex2f(0.0f, 0.0f);
	for (int i = 0; i <= 32; i++)
	{
		float aAngle = i * (2.0f * b2_pi) / 32;
		glVertex2f(0 + radius * std::cos(aAngle), 0 + radius * std::sin(aAngle));
	}
	glEnd();
	glPopMatrix();
}


#include "Box.h"
#include <box2d/box2d.h>
#include <GLFW/glfw3.h>

Box::Box(b2World* world)
    :firstFrame(true), mWorld(world), body()
{
    pos.first = 0;
    pos.second = 0;
}

void Box::setup(float x, float y)
{
    pos.first = x;
    pos.second = y;
    firstFrame = false;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.first, pos.second);
    body = mWorld->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}



void Box::drawRect()
{
    float rec1 = 0.5f;
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);
    glRotatef(angle * 180.0f / b2_pi, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-rec1, -rec1);
    glVertex2f(rec1, -rec1);
    glVertex2f(rec1, rec1);
    glVertex2f(-rec1, rec1);
    glEnd();
    glColor3f(0.2f, 0.6f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-rec1, -rec1);
    glVertex2f(-rec1, rec1);
    glVertex2f(-rec1, rec1);
    glVertex2f(rec1, rec1);
    glVertex2f(rec1, rec1);
    glVertex2f(rec1, -rec1);
    glVertex2f(rec1, -rec1);
    glVertex2f(-rec1, -rec1);
    glVertex2f(-rec1, -rec1);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

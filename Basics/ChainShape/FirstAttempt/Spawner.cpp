#include "Spawner.h"
#include <random>
#include "Circle.h"

//std::random_device rd;
//std::mt19937 gen(rd());
//std::uniform_real_distribution<float> dis(0.1f, 1.0f);

Spawner::Spawner(b2World* world)
:posX(0.0f), posY(0.0f), mWorld(world)
{
    rad = {};
    circs = {};
    count = 0;
}

void Spawner::setup(float x, float y)
{
    posX = x;
    posY = y;
}

void Spawner::update()
{
    count++;
    if (count % 20 == 0)
    {
        circs.push_back(Circle(mWorld));
        //rad.push_back(dis(gen));

        //int length = rad.size();

        //for (int i = 0; i < length; i++)
        //{
        //    circs[i].radius = rad[i];
        //}

        for (Circle& c : circs)
        {
            if (c.firstFrame)
            {
                c.setup(this->posX, this->posY);
            }
            c.draw();
        }
    }
}

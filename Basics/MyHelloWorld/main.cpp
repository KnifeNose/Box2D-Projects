#include <box2d/box2d.h>
#include <GLFW/glfw3.h>
#include "Box.h"
#include "Ground.h"
#include <vector>
#include <iostream>
#include <random>

float worldX = 0.0f;
float worldY = 0.0f;

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int winWidth = 640;
    int winHeight = 480;

    // Convert cursor position to world coordinates
    float world_x_range = 30.0f;
    float world_y_range = 30.0f;
    float world_x_offset = -15.0f;
    float world_y_offset = -15.0f;

    worldX = (float)xpos / winWidth * world_x_range + world_x_offset;
    worldY = (-(float)ypos / winHeight * world_y_range + world_y_offset) + 30;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    b2Vec2 gravity(0.0f, -1.0f);

    b2World world(gravity);

    //Box box(&world);

    Ground* ground1 = new Ground(&world, 5.0f, 1.0f, -9.0f, -12.0f);

    Ground* ground2 = new Ground(&world, 5.0f, 1.0f, 9.0f, -10.0f);

    std::vector<std::pair<float, float>> heightWidth;
    std::vector<Box> boxVec;

    ground1->setup();
    ground2->setup();

    int count = 0;

    // Set up the projection matrix for a 30x30 grid
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0f, 15.0f, -15.0f, 15.0f, -1.0f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        world.Step(1.0f / 60.0f, 6, 2);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.1f, 1.0f);

        float temp1 = dis(gen);
        float temp2 = dis(gen);
        std::pair<float, float> wH {temp1, temp2};

        glfwSetCursorPosCallback(window, cursor_position_callback);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            boxVec.push_back(Box(&world));
            heightWidth.push_back(wH);
           // std::cout << worldX << ' ' << worldY << std::endl;
        }

        if (count % 20 == 0)
        {
            boxVec.push_back(Box(&world));
            heightWidth.push_back(wH);
        }

        int amount = boxVec.size();

        for (int i = 0; i < amount; i++)
        {
            boxVec[i].height = heightWidth[i].first;
            boxVec[i].width = heightWidth[i].second;
        }

        for (auto& b : boxVec)
        {
            if (b.firstFrame)
            {
                b.setup(0.0f, 13.0f);
            }
            b.draw();
        }

        ground1->draw();
        ground2->draw();

        count++;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

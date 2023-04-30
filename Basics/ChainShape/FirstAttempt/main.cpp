#include <box2d/box2d.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <random>
#include "Circle.h"
#include "Spawner.h"


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

    Circle* circ = new Circle(&world);

    Spawner* firstSpawner = new Spawner(&world);

    // Set up the projection matrix for a 30x30 grid
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0f, 15.0f, -15.0f, 15.0f, -1.0f, 1.0f);

    firstSpawner->setup(0.0f, 12.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        world.Step(1.0f / 60.0f, 6, 2);

        glfwSetCursorPosCallback(window, cursor_position_callback);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {

        }

        firstSpawner->update();

        //std::cout << firstSpawner->count << std::endl;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

#include "Yama/Application.h"

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static GLFWwindow *s_Window;
static const int s_Width = 640, s_Height = 480;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

namespace Yama
{

    Application::Application()
    {
        if (!glfwInit())
        {
            std::cout << "Failed to initialize!" << std::endl;
        }

        s_Window = glfwCreateWindow(s_Width, s_Height, "CMake Lesson", NULL, NULL);
        if (!s_Window)
        {
            std::cout << "Failed to create window!" << std::endl;
            glfwTerminate();
        }

        glfwMakeContextCurrent(s_Window);

        // Initialize GLEW to setup the OpenGL Function pointers
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
        }

        glfwSetKeyCallback(s_Window, key_callback);
        glfwSwapInterval(1);

        glViewport(0, 0, s_Width, s_Height);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    }

    Application::~Application()
    {
        glfwDestroyWindow(s_Window);
        glfwTerminate();
    }

    void Application::Run()
    {
        while (!glfwWindowShouldClose(s_Window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_TRIANGLES);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.5f, -0.5f);
            glVertex2f(0.0f, 0.5f);
            glEnd();

            glfwSwapBuffers(s_Window);
            glfwPollEvents();
        }
    }

}
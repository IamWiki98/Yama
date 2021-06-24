#include "Yama/Platform/Windows/WindowsWindow.h"
#include "Yama/Core/Log.h"

#include "Yama/Events/ApplicationEvent.h"
#include "Yama/Events/KeyEvent.h"
#include "Yama/Events/MouseEvent.h"

namespace Yama
{

    static bool s_GLFWInitialized = false;

    static void GLFWerrorCallback(int error, const char* description)
    {
        YM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_Data.m_Title = props.m_Title;
        m_Data.m_Width = props.m_Width;
        m_Data.m_Height = props.m_Height;
        
        YM_CORE_INFO("Creating window: \"{0}\" ({1}, {2})",
         m_Data.m_Title, m_Data.m_Width, m_Data.m_Height);

        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            YM_CORE_ASSERT(success, "GLFW already initialized!");

            glfwSetErrorCallback(GLFWerrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.m_Width, (int)m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.m_Width = width;
            data.m_Height = height;

            WindowResizedEvent event(width, height);
            data.m_EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowClosedEvent event;
            data.m_EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.m_EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.m_EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.m_EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.m_EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.m_EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.m_EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.m_VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.m_VSync;
    }
}
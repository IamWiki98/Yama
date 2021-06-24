#include "Yama/Core/Application.h"
#include "Yama/Core/Log.h"
#include "Yama/Events/Event.h"
#include "Yama/Events/ApplicationEvent.h"
#include "Yama/Events/MouseEvent.h"
#include "Yama/Core/Window.h"
#include "Yama/Core/Common.h"

/*
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
*/


namespace Yama
{
    
    Application::Application()
    {
        Log::Init();
        YM_CORE_INFO("Application constructed...");
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Yama::Application::OnEvent));
    }

    Application::~Application()
    {
        YM_CORE_INFO("Application destructed...");
    }

    void Application::Run()
    {
        YM_CORE_INFO("Entering engine loop...");
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
        YM_CORE_INFO("Exiting engine loop...");
    }

    void Application::OnEvent(Event& e) 
    {
        YM_CORE_TRACE(e);
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
    }

    bool Application::OnWindowClosed(WindowClosedEvent& e)
    {
        m_Running = false;
        return true;
    }

}
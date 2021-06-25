#include "Yama/Core/Application.h"
#include "Yama/Core/Log.h"
#include "Yama/Core/Window.h"
#include "Yama/Core/Common.h"
#include "Yama/Core/Layer.h"

#include "Yama/Events/Event.h"
#include "Yama/Events/ApplicationEvent.h"
#include "Yama/Events/KeyEvent.h"

#include <GL/glew.h>

namespace Yama
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        YM_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        Log::Init();
        YM_CORE_INFO("Constructing application...");
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Yama::Application::OnEvent));

    }

    Application::~Application()
    {
        YM_CORE_INFO("Destructing application...");
    }

    void Application::Run()
    {
        YM_CORE_INFO("Entering engine loop...");
        while(m_Running)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
        YM_CORE_INFO("Exiting engine loop...");
    }

    void Application::OnEvent(Event& e) 
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e)
        {
            if(e.GetKeyCode() == 256)
            {
                m_Running = false;
                return true;
            }

            return false;
        });

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.m_Handled)
                break;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClosed(WindowClosedEvent& e)
    {
        m_Running = false;
        return true;
    }

}
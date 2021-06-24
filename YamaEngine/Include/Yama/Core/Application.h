#pragma once

#include "Yama/Core/Common.h"
#include <memory>

namespace Yama
{

    class Window;
    class Event;
    class WindowClosedEvent;

    class YAMA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Run();
    private:
        bool OnWindowClosed(WindowClosedEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };    

    // Needs to be defined in client
    Application* CreateApplication();

}
#pragma once

#include "Yama/Core/Common.h"
#include "Yama/Core/LayerStack.h"
#include <memory>

namespace Yama
{

    class Window;
    class Event;
    class WindowClosedEvent;
    class Layer;

    class YAMA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event& e);
        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline const Window& GetWindow() const { return *m_Window; }

        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClosed(WindowClosedEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        static Application* s_Instance;
    };    

    // Needs to be defined in client
    Application* CreateApplication();

}
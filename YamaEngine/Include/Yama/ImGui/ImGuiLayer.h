#pragma once

#include "Yama/Core/Layer.h"
#include "Yama/Core/Common.h"

namespace Yama
{
    class MouseButtonPressedEvent;
    class MouseButtonReleasedEvent;
    class MouseMovedEvent;
    class MouseScrolledEvent;
    class KeyPressedEvent;
    class KeyReleasedEvent;
    class KeyTypedEvent;
    class WindowResizedEvent;

    class YAMA_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& e);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizedEvent(WindowResizedEvent& e);
    private:
        float m_Time = 0.0f;
    };
}
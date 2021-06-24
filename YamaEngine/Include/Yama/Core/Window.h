#pragma once

#include "Yama/Core/Common.h"
#include "Yama/Events/Event.h"
#include <sstream>

namespace Yama
{

    struct WindowProps
    {
        std::string m_Title;
        unsigned int m_Width;
        unsigned int m_Height;

        WindowProps(
                const std::string& title = "Yama Engine",
                unsigned int width = 1280,
                unsigned int height = 720)
                : m_Title(title), m_Width(width), m_Height(height)
        {
        }
    };

    class YAMA_API Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        static Window* Create(const WindowProps &props = WindowProps());
    };
}
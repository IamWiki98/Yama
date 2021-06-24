#pragma once

#include "Yama/Events/Event.h"
#include <sstream>

namespace Yama
{
    class YAMA_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) :
            m_X(x), m_Y(y) {}

        inline float GetX() const { return m_X; }
        inline float GetY() const { return m_Y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_X << ", " << m_Y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_X;
        float m_Y;
    };

    class YAMA_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) :
            m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_XOffset;
        float m_YOffset;
    };

    // Base class
    class YAMA_API MouseButtonEvent : public Event
    {
    public:
        inline int GetButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
    protected:
        MouseButtonEvent(int button) :
            m_Button(button) {}

        int m_Button;
    };

    class YAMA_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) :
            MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class YAMA_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) :
            MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
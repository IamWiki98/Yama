#pragma once

#include "Yama/Events/Event.h"
#include <sstream>

namespace Yama
{

    class YAMA_API WindowResizedEvent : public Event
    {
    public:
        WindowResizedEvent(unsigned int width, unsigned int height) :
            m_Width(width), m_Height(height) {}

        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResized)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    class YAMA_API WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() = default;

        EVENT_CLASS_TYPE(WindowClosed)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class YAMA_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class YAMA_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class YAMA_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

}
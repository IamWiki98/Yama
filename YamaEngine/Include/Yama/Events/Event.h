#pragma once

#include "Yama/Core/Core.h"
#include <string>
#include <functional>

// Event system used by TheCherno

namespace Yama
{

    enum class EventType
    {
        None = 0,
        // Window
        WindowClosed,
        WindowResized,
        WindowFocused,
        WindowLostFocus,
        WindowMoved,
        // App
        AppTick,
        AppUpdate,
        AppRender,
        // Keyboard, Controller
        KeyPressed,
        KeyReleased,
        KeyTyped,
        // Mouse
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication =   BIT(0),
        EventCategoryInput =         BIT(1),
        EventCategoryKeyboard =      BIT(2),
        EventCategoryMouse =         BIT(3),
        EventCategoryMouseButton =   BIT(4)
    };


// Get static type of the class using the definition and define the other abstract functions
#define EVENT_CLASS_TYPE(type)                                                  \
    inline static EventType GetStaticType() { return EventType::type; }         \
    virtual EventType GetType() const override { return GetStaticType(); }      \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    class YAMA_API Event
    {
        friend class EventDispatcher;
    public:
        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual inline std::string ToString() const { return GetName(); }

        inline bool IsInCatergory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

    protected:
        bool m_Handled = false;
    };

    class YAMA_API EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) :
            m_Event(event)
        {

        }

        template<typename T, typename F>
        bool Dispatch(EventFn<F> fnCallback)
        {
            if(m_Event.GetType() == T::GetStaticType())
            {
                m_Event = fnCallback(static_cast<T&>(m_Event));
                return true;
            }

            return false;
        }

        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}
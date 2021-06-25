#pragma once

#include "Yama/Core/Common.h"
#include <string>

namespace Yama
{
    class Event;

    class YAMA_API Layer
    {
    public:
        Layer(std::string name = "Unnamed Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event &e) {}

        inline const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}
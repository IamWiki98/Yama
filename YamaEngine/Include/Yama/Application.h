#pragma once

#include "Core.h"

namespace Yama
{

    class YAMA_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // Needs to be defined in client
    Application* Create();

}
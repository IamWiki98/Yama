#include "Yama/Core/Application.h"
#include "Yama/Core/Log.h"

/*
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
*/

#include "Yama/Events/ApplicationEvent.h"
namespace Yama
{

    Application::Application()
    {
        Log::Init();
        YM_CORE_INFO("Application constructed...");
    }

    Application::~Application()
    {
        YM_CORE_INFO("Application destructed...");
    }

    void Application::Run()
    {
        WindowResizedEvent e(1280, 720);
        YM_TRACE(e);

        YM_CORE_INFO("Entering engine loop...");
        while(true)
        {
            
        }
        YM_CORE_INFO("Exiting engine loop...");
    }

    void Application::OnEvent() 
    {
        
    }

}
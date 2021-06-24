#include "Yama/Core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Yama 
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() 
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        if(!s_CoreLogger)
        {
            s_CoreLogger = spdlog::stdout_color_mt("YAMA");
            s_CoreLogger->set_level(spdlog::level::trace);
        }

        if(!s_ClientLogger)
        {
            s_ClientLogger = spdlog::stdout_color_mt("APP");
            s_ClientLogger->set_level(spdlog::level::trace);
        }

        YM_CORE_INFO("Loggers initialized...");
    }
}
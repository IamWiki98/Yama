#pragma once

#include "Yama/Core/Common.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>

namespace Yama 
{

    class YAMA_API Log 
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
    
}

// Core log macros
#define YM_CORE_TRACE(...)      ::Yama::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YM_CORE_INFO(...)       ::Yama::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YM_CORE_WARN(...)       ::Yama::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YM_CORE_ERROR(...)      ::Yama::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YM_CORE_CRITICAL(...)   ::Yama::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define YM_TRACE(...)           ::Yama::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YM_INFO(...)            ::Yama::Log::GetClientLogger()->info(__VA_ARGS__)
#define YM_WARN(...)            ::Yama::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YM_ERROR(...)           ::Yama::Log::GetClientLogger()->error(__VA_ARGS__)
#define YM_CRITICAL(...)        ::Yama::Log::GetClientLogger()->critical(__VA_ARGS__)
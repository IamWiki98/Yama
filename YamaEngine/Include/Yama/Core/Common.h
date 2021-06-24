#pragma once

#ifdef YM_PLATFORM_WINDOWS
    #ifdef YM_BUILD_DLL
        #define YAMA_API __declspec(dllexport)
    #else
        #define YAMA_API __declspec(dllimport)
    #endif
#else
    #define YAMA_API
#endif

// CMake doesn't let you use definitions per configuration
#ifndef NDEBUG
    // DEBUG MODE
    #define YM_ENABLE_ASSERTS
#else
    // RELEASE MODE
#endif

#ifdef YM_ENABLE_ASSERTS
    #if defined(_WIN32) || defined(__GNUC__)
        #define YM_CORE_ASSERT(x, ...)                               \
            if (!(x))                                                \
            {                                                        \
                YM_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                __debugbreak();                                      \
            }
        #define YM_ASSERT(x, ...)                                    \
            if (!(x))                                                \
            {                                                        \
                YM_ERROR("Assertion failed: {0}", __VA_ARGS__);      \
                __debugbreak();                                      \
            }
    #else
        #define YM_CORE_ASSERT(x, ...)                               \
            if (!(x))                                                \
            {                                                        \
                YM_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
                abort();                                             \
            }
        #define YM_ASSERT(x, ...)                                    \
            if (!(x))                                                \
            {                                                        \
                YM_ERROR("Assertion failed: {0}", __VA_ARGS__);      \
                abort();                                             \
            }
    #endif
#else
    #define YM_CORE_ASSERT(x, ...)
    #define YM_ASSERT(x, ...)
#endif

#define BIT(x) (x << 1)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
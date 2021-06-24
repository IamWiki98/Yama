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

#define BIT(x) (x << 1)
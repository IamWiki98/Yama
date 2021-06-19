#pragma once

#ifdef YM_PLATFORM_WINDOWS

extern Yama::Application* Yama::Create();

int main(int argc, char** argv)
{
    auto app = Yama::Create();
    app->Run();
    delete app;
}

#else

#endif
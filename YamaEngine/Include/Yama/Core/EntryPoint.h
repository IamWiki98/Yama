#pragma once

extern Yama::Application* Yama::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Yama::CreateApplication();
    app->Run();
    delete app;
}

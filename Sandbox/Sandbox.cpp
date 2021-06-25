#include <Yama.h>

class ExampleLayer : public Yama::Layer
{
public:
    ExampleLayer() :
        Layer("Example") {}

    void OnUpdate() override
    {
    }

    void OnEvent(Yama::Event& e) override
    {
    }
};

class Sandbox : public Yama::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Yama::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

Yama::Application* Yama::CreateApplication()
{
    return new Sandbox();
}
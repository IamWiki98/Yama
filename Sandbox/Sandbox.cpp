#include <Yama.h>

class Sandbox : public Yama::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Yama::Application* Yama::Create()
{
    return new Sandbox();
}
#pragma once

#include "Yama/Core/Window.h"
#include "GLFW/glfw3.h"

namespace Yama
{

    class YAMA_API WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps &props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.m_Width; }
		unsigned int GetHeight() const override { return m_Data.m_Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.m_EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;
    private:
        void Init(const WindowProps &props);
        void Shutdown();
    private:
        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string m_Title;
            unsigned int m_Width;
            unsigned int m_Height;
            bool m_VSync;

            EventCallbackFn m_EventCallback;
        };

        WindowData m_Data;
    };
}
#pragma once

#include "engine/event/Event.hpp"
#include "engine/Logger.hpp"

#include <GLFW/glfw3.h>
#include <string>

namespace engine {
    struct WindowData {
        std::string title = "Window";
        unsigned int width = 640;
        unsigned int height = 480;
        bool fullscreen = false;
        bool vSync = true;
        EventCallbackFn_t eventCallback = [&](const Event&) {
            TF_ENGINE_ERROR("Event callback not set on window {}", title);
        };
    };

    class Window {
    public:
        Window();
        ~Window();

        void onUpdate() const;

        static void initGLFW();
        static void terminateGLFW();

        void setTitle(const std::string& title);
        void setSize(int width, int height) const;
        void maximize() const;
        void setFullscreen(bool fullscreen);
        void setVSync(bool enabled);
        void setEventCallback(const EventCallbackFn_t& eventCallback);

        [[nodiscard]] const WindowData& getData() const { return m_data; }
        [[nodiscard]] GLFWwindow* getNativeWindow() const { return m_nativeWindow; }

    private:
        WindowData m_data;
        GLFWwindow* m_nativeWindow;
    };
}

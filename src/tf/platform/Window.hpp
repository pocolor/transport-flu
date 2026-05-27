#pragma once

#include "tf/core.hpp"

#include "tf/event/Event.hpp"

#include <GLFW/glfw3.h>

namespace tf {
    struct WindowData {
        str title = "Window";
        unsigned int width = 640;
        unsigned int height = 480;
        bool fullscreen = false;
        bool vSync = true;
        EventCallbackFn eventCallback = [&](const Event&) {
            TF_ENGINE_ERROR("Event callback not set on window {}", title);
        };
    };

    class Window {
    public:
        Window();
        ~Window();

        void onUpdate() const;

        void setTitle(const str& title);
        void setSize(int width, int height) const;
        void maximize() const;
        void setFullscreen(bool fullscreen);
        void setVSync(bool enabled);
        void setEventCallback(const EventCallbackFn& eventCallback);

        const WindowData& getData() const { return m_data; }
        GLFWwindow* getHandle() const { return m_handle; }

    private:
        WindowData m_data;
        GLFWwindow* m_handle;
    };
}

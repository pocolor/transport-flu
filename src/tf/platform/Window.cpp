#include "tf/pch.hpp"

#include "Window.hpp"

#include "tf/event/Event.hpp"
#include "tf/event/ApplicationEvent.hpp"

#include <glad/glad.h>

namespace tf {
    static void glfwErrorCallback(int error_code, const char* description) {
        TF_ENGINE_ERROR("GLFW error, code={0}, description={1}", error_code, description);
    }

    Window::Window() {
        m_handle = glfwCreateWindow(
            m_data.width,
            m_data.height,
            m_data.title.c_str(),
            nullptr,
            nullptr
        );
        TF_ENGINE_ASSERT(m_handle);

        glfwMakeContextCurrent(m_handle);
        const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        TF_ENGINE_ASSERT(status);
        setVSync(m_data.vSync);

        // glfw callbacks
        glfwSetWindowUserPointer(m_handle, &m_data);
#define DATA WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window)
#define EVENT(event) auto evnt = event;\
data.eventCallback(evnt)

        glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height) {
            DATA;
            data.width = width;
            data.height = height;
            EVENT(WindowResizeEvent(width, height, data.fullscreen));
        });

        glfwSetWindowFocusCallback(m_handle, [](GLFWwindow* window, int focused) {
            const DATA;
            if (focused) {
                EVENT(WindowFocusEvent());
            } else {
                EVENT(WindowLostFocusEvent());
            }
        });

        glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window) {
            const DATA;
            EVENT(WindowCloseEvent());
        });

#undef DATA
#undef EVENT
    }

    Window::~Window() {
        glfwDestroyWindow(m_handle);
    }

    void Window::initGLFW() {
        const int success = glfwInit();
        TF_ENGINE_ASSERT(success);

        glfwSetErrorCallback(glfwErrorCallback);
    }

    void Window::terminateGLFW() {
        glfwTerminate();
    }

    void Window::onUpdate() const {
        glfwSwapBuffers(m_handle);
        glfwPollEvents();
    }

    void Window::setTitle(const str& title) {
        glfwSetWindowTitle(m_handle, title.c_str());
        m_data.title = title;
    }

    void Window::setSize(int width, int height) const {
        glfwSetWindowSize(m_handle, width, height);
    }

    void Window::maximize() const {
        glfwMaximizeWindow(m_handle);
    }

    void Window::setFullscreen(bool fullscreen) {
        if (fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(
                m_handle,
                monitor,
                0, 0,
                mode->width,
                mode->height,
                mode->refreshRate
            );
        } else
            glfwSetWindowSize(m_handle, m_data.width, m_data.height);
        m_data.fullscreen = fullscreen;
    }

    void Window::setVSync(bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_data.vSync = enabled;
    }

    void Window::setEventCallback(const EventCallbackFn& eventCallback) {
        m_data.eventCallback = eventCallback;
    }
}
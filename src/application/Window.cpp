#include "engine/application/Window.hpp"

#include "engine/event/Event.hpp"
#include "engine/event/ApplicationEvent.hpp"
#include "engine/event/KeyEvent.hpp"
#include "engine/event/MouseEvent.hpp"

#include "engine/Logger.hpp"

#include <glad/glad.h>

namespace engine {
    static void glfwErrorCallback(int error_code, const char* description) {
        TF_ENGINE_ERROR("GLFW error, code={0}, description={1}", error_code, description);
    }

    Window::Window() {
        m_nativeWindow = glfwCreateWindow(
            (int) m_data.width,
            (int) m_data.height,
            m_data.title.c_str(),
            nullptr,
            nullptr
        );
        TF_ENGINE_ASSERT(m_nativeWindow);

        glfwMakeContextCurrent(m_nativeWindow);
        const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        TF_ENGINE_ASSERT(status);
        setVSync(m_data.vSync);

        // glfw callbacks
        glfwSetWindowUserPointer(m_nativeWindow, &m_data);
#define DATA WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window)
#define EVENT(event) auto evnt = event;\
data.eventCallback(evnt)

        glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height) {
            DATA;
            data.width = width;
            data.height = height;
            EVENT(WindowResizeEvent(width, height, data.fullscreen));
        });

        glfwSetWindowFocusCallback(m_nativeWindow, [](GLFWwindow* window, int focused) {
            const DATA;
            if (focused) {
                EVENT(WindowFocusEvent());
            } else {
                EVENT(WindowLostFocusEvent());
            }
        });

        glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* window) {
            const DATA;
            EVENT(WindowCloseEvent());
        });

        glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            const DATA;

            switch (action) {
                case GLFW_PRESS: {
                    EVENT(KeyPressedEvent(key));
                    break;
                }
                case GLFW_RELEASE: {
                    EVENT(KeyReleasedEvent(key));
                    break;
                }
                case GLFW_REPEAT: {
                    EVENT(KeyRepeatEvent(key));
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods) {
            const DATA;

            switch (action) {
                case GLFW_PRESS: {
                    EVENT(MouseButtonPressedEvent(button));
                    break;
                }
                case GLFW_RELEASE: {
                    EVENT(MouseButtonReleasedEvent(button));
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
            const DATA;
            EVENT(MouseScrolledEvent((float) xOffset, (float) yOffset));
        });

        glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xPos, double yPos) {
            const DATA;
            EVENT(MouseMovedEvent((float) xPos, (float) yPos));
        });

#undef DATA
#undef EVENT
    }

    Window::~Window() {
        glfwDestroyWindow(m_nativeWindow);
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
        glfwSwapBuffers(m_nativeWindow);
        glfwPollEvents();
    }

    void Window::setTitle(const std::string& title) {
        glfwSetWindowTitle(m_nativeWindow, title.c_str());
        m_data.title = title;
    }

    void Window::setSize(const int width, const int height) const {
        glfwSetWindowSize(m_nativeWindow, width, height);
    }

    void Window::maximize() const {
        glfwMaximizeWindow(m_nativeWindow);
    }

    void Window::setFullscreen(const bool fullscreen) {
        if (fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(
                m_nativeWindow,
                monitor,
                0, 0,
                mode->width,
                mode->height,
                mode->refreshRate
            );
        } else
            glfwSetWindowSize(m_nativeWindow, (int) m_data.width, (int) m_data.height);
        m_data.fullscreen = fullscreen;
    }

    void Window::setVSync(const bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_data.vSync = enabled;
    }

    void Window::setEventCallback(const EventCallbackFn_t &eventCallback) {
        m_data.eventCallback = eventCallback;
    }
}
#include "tf/pch.hpp"

#include "tf/platform/Application.hpp"
#include "tf/platform/Window.hpp"

int main() {
    using namespace tf;

    Logger::init();
    Window::initGLFW();

    {
        Application app;
        app.run();
    }

    Window::terminateGLFW();
}

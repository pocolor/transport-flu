#pragma once

#include "engine/Logger.hpp"
#include "engine/application/Application.hpp"
#include "engine/application/Window.hpp"

extern engine::Application* createApplication();

int main() {
    using namespace engine;

    Logger::init();
    Window::initGLFW();

    Application* app = createApplication();
    app->onInit();

    app->run();

    app->onTerminate();
    delete app;

    Window::terminateGLFW();
}

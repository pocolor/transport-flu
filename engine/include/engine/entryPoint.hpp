#pragma once

#include "engine/Logger.hpp"
#include "engine/application/Application.hpp"

extern engine::Application* createApplication();

int main() {
    engine::Logger::init();

    engine::Application* app = createApplication();
    app->onInit();
    app->run();
    app->onDestroy();
    delete app;
}

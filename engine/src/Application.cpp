#include "engine/Application.hpp"

#include "engine/Logger.hpp"

namespace engine {
    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::run() {
        onStart();

        while (true) {
            TF_ENGINE_INFO("App running");
        }

        onStop();
    }
}

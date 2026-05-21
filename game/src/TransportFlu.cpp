#include "engine/entryPoint.hpp"

class TransportFluApp : public engine::Application {
public:
    void onInit() override {}

    void onStart() override {}

    void onStop() override {}

    void onDestroy() override {}
};

engine::Application* createApplication() {
    return new TransportFluApp;
}
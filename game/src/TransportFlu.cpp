#include "engine/entryPoint.hpp"

class TransportFluApp : public engine::Application {
public:
    void onInit() override {
        TF_INFO("TransportFlu init");
        getWindow().setTitle("Transport Flu");
    }

    void onStart() override {
        TF_INFO("TransportFlu start");
    }

    void onStop() override {
        TF_INFO("TransportFlu stop");
    }

    void onTerminate() override {
        TF_INFO("TransportFlu terminate");
    }
};

engine::Application* createApplication() {
    return new TransportFluApp;
}
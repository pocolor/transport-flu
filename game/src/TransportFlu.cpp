#include "engine/entryPoint.hpp"

#include "game/TestLayer.hpp"

class TransportFluApp : public engine::Application {
public:
    void onInit() override {
        TF_INFO("TransportFlu init");
        getWindow().setTitle("Transport Flu");

        getLayerStack().pushLayer(new TestLayer);
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
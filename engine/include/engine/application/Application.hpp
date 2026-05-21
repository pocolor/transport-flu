#pragma once

namespace engine {
    class Application {
    protected:
        Application();

    public:
        virtual ~Application();

        virtual void onInit() {}
        virtual void onStart() {}
        virtual void onStop() {}
        virtual void onDestroy() {}

        void run();
    };
}

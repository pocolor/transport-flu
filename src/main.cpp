#include "tf/pch.hpp"

#include "tf/platform/Application.hpp"
#include "tf/platform/input/Input.hpp"

int main() {
    using namespace tf;

    Logger::init();
    Input::init();

    Application app;
    app.run();
}

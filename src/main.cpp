#include "tf/pch.hpp"

#include "tf/platform/Application.hpp"
#include "tf/platform/Time.hpp"
#include "tf/platform/input/Input.hpp"

int main() {
    using namespace tf;

    Logger::init();

    Application app;
    const auto handle = app.getWindow().getHandle();

    Time::init(handle);
    Input::init(handle);

    app.run();
}

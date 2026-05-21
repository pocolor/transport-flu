#include "engine/Logger.hpp"

#include <vector>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace engine {
    std::shared_ptr<spdlog::logger> Logger::s_engineLogger;
    std::shared_ptr<spdlog::logger> Logger::s_clientLogger;

    void Logger::init() {
        auto engineConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        engineConsoleSink->set_level(spdlog::level::trace);
        engineConsoleSink->set_pattern("%^[%T.%e] [%n] [%l] %s:%# %!(): %v%$");

        auto engineFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/engine.log",
            1024 * 1024 * 5,
            3);
        engineFileSink->set_level(spdlog::level::info);
        engineFileSink->set_pattern("[%Y-%m-%d %T] [%l] %v");

        std::vector<spdlog::sink_ptr> engineSinks = { engineConsoleSink, engineFileSink };
        s_engineLogger = std::make_shared<spdlog::logger>(
            "ENGINE",
            engineSinks.begin(),
            engineSinks.end());

        auto clientConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        clientConsoleSink->set_level(spdlog::level::trace);
        clientConsoleSink->set_pattern("%^[%T.%e] [%n] [%l] %s:%# %!(): %v%$");

        auto clientFileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/client.log",
            1024 * 1024 * 5,
            3);
        clientFileSink->set_level(spdlog::level::info);
        clientFileSink->set_pattern("[%Y-%m-%d %T] [%l] %v");

        std::vector<spdlog::sink_ptr> clientSinks = { clientConsoleSink, clientFileSink };
        s_clientLogger = std::make_shared<spdlog::logger>(
            "CLIENT",
            clientSinks.begin(),
            clientSinks.end());
    }
}

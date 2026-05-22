#include "engine/Logger.hpp"

#include <vector>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace engine {
    std::shared_ptr<spdlog::logger> Logger::s_engineLogger;
    std::shared_ptr<spdlog::logger> Logger::s_clientLogger;
/*
#define SPDLOG_LEVEL_TRACE 0
#define SPDLOG_LEVEL_DEBUG 1
#define SPDLOG_LEVEL_INFO 2
#define SPDLOG_LEVEL_WARN 3
#define SPDLOG_LEVEL_ERROR 4
#define SPDLOG_LEVEL_CRITICAL 5
#define SPDLOG_LEVEL_OFF 6
*/

    void Logger::init() {
        constexpr spdlog::level::level_enum logLevels[] = {
            spdlog::level::trace,
            spdlog::level::debug,
            spdlog::level::info,
            spdlog::level::warn,
            spdlog::level::err,
            spdlog::level::critical,
        };

        constexpr spdlog::level::level_enum logLevel = logLevels[SPDLOG_ACTIVE_LEVEL];

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

        s_engineLogger->set_level(logLevel);
        s_engineLogger->flush_on(logLevel);

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

        s_clientLogger->set_level(logLevel);
        s_clientLogger->flush_on(logLevel);
    }
}

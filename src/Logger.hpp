#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace engine {
    class Logger {
    public:
        Logger() = delete;

        static void init();

        static std::shared_ptr<spdlog::logger>& getEngineLogger() { return s_engineLogger; }
        static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_engineLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };
}

#ifdef TF_BUILD_DEBUG

#ifdef _MSC_VER
#define TF_DEBUGBREAK() __debugbreak()
#else
#include <csignal>
#define TF_DEBUGBREAK() raise(SIGTRAP)
#endif

#define TF_IMPL_TRACE(func, ...) SPDLOG_LOGGER_TRACE(engine::Logger::func(), __VA_ARGS__)
#define TF_IMPL_DEBUG(func, ...) SPDLOG_LOGGER_DEBUG(engine::Logger::func(), __VA_ARGS__)
#define TF_IMPL_INFO(func, ...) SPDLOG_LOGGER_INFO(engine::Logger::func(), __VA_ARGS__)
#define TF_IMPL_WARN(func, ...) SPDLOG_LOGGER_WARN(engine::Logger::func(), __VA_ARGS__)
#define TF_IMPL_ERROR(func, ...) SPDLOG_LOGGER_ERROR(engine::Logger::func(), __VA_ARGS__)
#define TF_IMPL_CRITICAL(func, ...) SPDLOG_LOGGER_CRITICAL(engine::Logger::func(), __VA_ARGS__)

#define TF_IMPL_ASSERT(func, condition) \
    do { \
        if (!(condition)) { \
            TF_IMPL_CRITICAL(func, "Assertion '{}' failed", #condition); \
            TF_DEBUGBREAK(); \
        } \
    } while (false)

#define TF_IMPL_ASSERT_M(func, condition, ...) \
    do { \
        if (!(condition)) { \
            TF_IMPL_CRITICAL(func, "Assertion '{}' failed: {}", #condition, fmt::format(__VA_ARGS__)); \
            TF_DEBUGBREAK(); \
        } \
    } while (false)

#else

#define TF_DEBUGBREAK()

#define TF_IMPL_TRACE(func, ...)
#define TF_IMPL_DEBUG(func, ...)
#define TF_IMPL_INFO(func, ...)
#define TF_IMPL_WARN(func, ...)
#define TF_IMPL_ERROR(func, ...)
#define TF_IMPL_CRITICAL(func, ...)

#define TF_IMPL_ASSERT(func, condition)
#define TF_IMPL_ASSERT_M(func, condition, ...)

#endif

#define TF_ENGINE_TRACE(...) TF_IMPL_TRACE(getEngineLogger, __VA_ARGS__)
#define TF_ENGINE_DEBUG(...) TF_IMPL_DEBUG(getEngineLogger, __VA_ARGS__)
#define TF_ENGINE_INFO(...) TF_IMPL_INFO(getEngineLogger, __VA_ARGS__)
#define TF_ENGINE_WARN(...) TF_IMPL_WARN(getEngineLogger, __VA_ARGS__)
#define TF_ENGINE_ERROR(...) TF_IMPL_ERROR(getEngineLogger, __VA_ARGS__)
#define TF_ENGINE_CRITICAL(...) TF_IMPL_CRITICAL(getEngineLogger, __VA_ARGS__)

#define TF_ENGINE_ASSERT(condition) TF_IMPL_ASSERT(getEngineLogger, condition)
#define TF_ENGINE_ASSERT_M(condition, ...) TF_IMPL_ASSERT_M(getEngineLogger, condition, __VA_ARGS__)

#define TF_TRACE(...) TF_IMPL_TRACE(getClientLogger, __VA_ARGS__)
#define TF_DEBUG(...) TF_IMPL_DEBUG(getClientLogger, __VA_ARGS__)
#define TF_INFO(...) TF_IMPL_INFO(getClientLogger, __VA_ARGS__)
#define TF_WARN(...) TF_IMPL_WARN(getClientLogger, __VA_ARGS__)
#define TF_ERROR(...) TF_IMPL_ERROR(getClientLogger, __VA_ARGS__)
#define TF_CRITICAL(...) TF_IMPL_CRITICAL(getClientLogger, __VA_ARGS__)

#define TF_ASSERT(condition) TF_IMPL_ASSERT(getClientLogger, condition)
#define TF_ASSERT_M(condition, ...) TF_IMPL_ASSERT_M(getClientLogger, condition, __VA_ARGS__)

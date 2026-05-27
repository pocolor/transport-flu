#pragma once

#include <spdlog/spdlog.h>

#include <memory>

namespace tf {
    class Logger {
    public:
        Logger() = delete;

        static void init();

        static std::shared_ptr<spdlog::logger>& getEngineLogger() { return s_engineLogger; }
        static std::shared_ptr<spdlog::logger>& getGameLogger() { return s_gameLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_engineLogger;
        static std::shared_ptr<spdlog::logger> s_gameLogger;
    };
}

#ifdef TF_BUILD_DEBUG

#ifdef _MSC_VER
#define TF_DEBUGBREAK() __debugbreak()
#else
#include <csignal>
#define TF_DEBUGBREAK() raise(SIGTRAP)
#endif

#define TF_IMPL_TRACE(func, ...) SPDLOG_LOGGER_TRACE(tf::Logger::func(), __VA_ARGS__)
#define TF_IMPL_DEBUG(func, ...) SPDLOG_LOGGER_DEBUG(tf::Logger::func(), __VA_ARGS__)
#define TF_IMPL_INFO(func, ...) SPDLOG_LOGGER_INFO(tf::Logger::func(), __VA_ARGS__)
#define TF_IMPL_WARN(func, ...) SPDLOG_LOGGER_WARN(tf::Logger::func(), __VA_ARGS__)
#define TF_IMPL_ERROR(func, ...) SPDLOG_LOGGER_ERROR(tf::Logger::func(), __VA_ARGS__)
#define TF_IMPL_CRITICAL(func, ...) SPDLOG_LOGGER_CRITICAL(tf::Logger::func(), __VA_ARGS__)

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

#define TF_TRACE(...) TF_IMPL_TRACE(getGameLogger, __VA_ARGS__)
#define TF_DEBUG(...) TF_IMPL_DEBUG(getGameLogger, __VA_ARGS__)
#define TF_INFO(...) TF_IMPL_INFO(getGameLogger, __VA_ARGS__)
#define TF_WARN(...) TF_IMPL_WARN(getGameLogger, __VA_ARGS__)
#define TF_ERROR(...) TF_IMPL_ERROR(getGameLogger, __VA_ARGS__)
#define TF_CRITICAL(...) TF_IMPL_CRITICAL(getGameLogger, __VA_ARGS__)

#define TF_ASSERT(condition) TF_IMPL_ASSERT(getGameLogger, condition)
#define TF_ASSERT_M(condition, ...) TF_IMPL_ASSERT_M(getGameLogger, condition, __VA_ARGS__)

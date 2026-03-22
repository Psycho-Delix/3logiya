#pragma once

#include <vector>
#include <memory>
#include <format>

#include "log_event.hpp"
#include "sink/sink.hpp"
#include "formatter/formatter.hpp"

class Logger
{
public:
    Logger() = default;
    /**
     * необходимо удалить, так как нельзя копировать _sinks
     *////////////////////////////////////////////////
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    //////////////////////////////////////////////////

    /**
     * для перемещения _sinks
     */
    Logger(Logger&& other) noexcept;

    /**
     * статический метод для создания глобального логгера
     */
    static Logger& create();
    /**
     * статический метод, возвращающий указатель на активный глобальный логгер
     */
    static Logger* active();

    /**
     * методы для фильтрации на уровне логгера
     *////////////////////////////////////////////////
    Logger& filter(LogLevel level) &;
    Logger&& filter(LogLevel level) &&;
    //////////////////////////////////////////////////

    /**
     * методы для конфигурации логгера
     *////////////////////////////////////////////////
    Logger& to_console() &;
    Logger&& to_console() &&;

    Logger& to_console(std::optional<LogLevel> level) &;
    Logger&& to_console(std::optional<LogLevel> level) &&;

    Logger& to_file(const std::string& path) &;
    Logger&& to_file(const std::string& path) &&;

    Logger& to_file(const std::string& path, std::optional<LogLevel> level) &;
    Logger&& to_file(const std::string& path, std::optional<LogLevel> level) &&;
    //////////////////////////////////////////////////
    
    Logger& clear_sinks() &;
    Logger&& clear_sinks() &&;

    /**
     * логирование по определенному уровню
     *////////////////////////////////////////////////
    template <typename... Args>
    void info(std::format_string<Args...> message, Args&&... args);

    template <typename... Args>
    void error(std::format_string<Args...> message, Args&&... args);

    template <typename... Args>
    void debug(std::format_string<Args...> message, 
               const char* file,
               int line,
               const char* function,
               Args&&... args);
    //////////////////////////////////////////////////

private:
    void log(const LogEvent& event);
    std::string current_timestamp();
    void add_sink(std::unique_ptr<Sink> sink);

private:
    /**
     *  мб смартпоинтер ебануть вхвхвхвх
     */ 
    static Logger* _active_logger;

    std::vector<std::unique_ptr<Sink>> _sinks;
    std::optional<LogLevel> _filter_level;
    mutable std::mutex _mutex;
};

#define LOG_INFO(msg, ...) \
    if (Logger::active()) Logger::active()->info(msg,  ##__VA_ARGS__)

#define LOG_ERROR(msg, ...) \
    if (Logger::active()) Logger::active()->error(msg,  ##__VA_ARGS__)

#ifdef NDEBUG
    #define LOG_DEBUG(...) 
#else
    #define LOG_DEBUG(msg, ...) \
        if (Logger::active()) Logger::active()->debug(msg, __FILE__, __LINE__, __func__,  ##__VA_ARGS__)
#endif

/**
 * метод для логов уровня INFO
 */
template <typename... Args>
void Logger::info(std::format_string<Args...> message, Args&&... args) {
    std::string msg = std::format(message, std::forward<Args>(args)...);
    log(LogEvent{
        current_timestamp(), 
        LogLevel::INFO, 
        std::move(msg)
    });
}

/**
 * метод для логов уровня ERROR
 */
template <typename... Args>
void Logger::error(std::format_string<Args...> message, Args&&... args) {
    std::string msg = std::format(message, std::forward<Args>(args)...);
    log(LogEvent{
        current_timestamp(), 
        LogLevel::ERROR, 
        std::move(msg)
    });
}

/**
 * метод для логов уровня DEBUG
 */
template <typename... Args>
void Logger::debug(std::format_string<Args...>  message, 
                   const char* file,
                   int line,
                   const char* function,
                   Args&&... args) 
{
    std::string msg = std::format(message, std::forward<Args>(args)...);
    log(LogEvent(
        current_timestamp(),
        LogLevel::DEBUG,
        msg,
        file,
        line,
        function
    ));
}

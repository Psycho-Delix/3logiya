#pragma once

#include <vector>
#include <memory>

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

    Logger& to_file(const std::string& path) &;
    Logger&& to_file(const std::string& path) &&;
    //////////////////////////////////////////////////

    /**
     * логирование по определенному уровню
     *////////////////////////////////////////////////
    void info(const std::string& message);
    void error(const std::string& message);
    void debug(const std::string& message, 
               const char* file,
               int line,
               const char* function);
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
    /**
     *  убрать поинтер
     */ 
    std::unique_ptr<LogLevel> _filter_level;
};

#define LOG_INFO(msg) \
    if (Logger::active()) Logger::active()->info(msg)

#define LOG_ERROR(msg) \
    if (Logger::active()) Logger::active()->error(msg)

#ifdef NDEBUG
    #define LOG_DEBUG(...) 
#else
    #define LOG_DEBUG(msg) \
        if (Logger::active()) Logger::active()->debug(msg, __FILE__, __LINE__, __func__)
#endif
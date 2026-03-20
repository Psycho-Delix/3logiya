#include "logger/logger.hpp"

#include <chrono>
#include <ctime>

#include "logger/sink/console_sink.hpp"
#include "logger/sink/file_sink.hpp"

Logger* Logger::_active_logger = nullptr;

Logger::Logger(Logger&& other) noexcept
:
    _sinks(std::move(other._sinks))
{
    if (_active_logger == &other) {
        _active_logger = this;
    }
}

Logger& Logger::create() {
    /**
     * возвращаю ссылку на статический объект логгера, 
     * глобальный логгер должен жить все время программы
     */
    static Logger logger;
    _active_logger = &logger;
    return logger;
}

Logger* Logger::active() {
    return _active_logger;
}

Logger& Logger::filter(LogLevel level) & {
    _filter_level = std::make_unique<LogLevel>(level);
    return *this;
}

Logger&& Logger::filter(LogLevel level) && {
    _filter_level = std::make_unique<LogLevel>(level);
    return std::move(*this);
}

/**
 * методы для добавления стратегии записи 
 */
/////////////////////////////////////////////// 
Logger& Logger::to_console() & {
    add_sink(std::make_unique<ConsoleSink>());
    return *this;
}

Logger&& Logger::to_console() && {
    to_console();
    return std::move(*this);
}

Logger& Logger::to_file(const std::string& path) & {
    add_sink(std::make_unique<FileSink>(path));
    return *this;
}

Logger&& Logger::to_file(const std::string& path) && {
    to_file(path);
    return std::move(*this);
}
/////////////////////////////////////////////// 

/**
 * основной метод логгера, которая принимает на вход событие и выводит его в консоль.
 * вывод логера осуществляется в выбранной стратегии
 */
void Logger::log(const LogEvent& event) {
    /**
     * если нет указания по фильтру - пишем все
     */
    if (!_filter_level) {
        for (auto& sink : _sinks) {
            sink->write(event);
        }
    }
    /**
     * иначе пишем по конкретному фильтру
     */
    else if (event.level == *_filter_level) {
        for (auto& sink : _sinks) {
            sink->write(event);
        }
    }
}

/**
 * метод для получения текущего времени в виде строки.
 * используется для всех лог-сообщений, чтобы было понятно когда произошла запись.
 */
std::string Logger::current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now_time)); // возможно добавлю миллисекунды
    return std::string(buf);
}

void Logger::add_sink(std::unique_ptr<Sink> sink) {
    _sinks.push_back(std::move(sink));
}
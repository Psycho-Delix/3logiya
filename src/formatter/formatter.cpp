#include "logger/formatter/formatter.hpp"

#include <cstring>

std::string Formatter::format(const LogEvent& event) {
    switch (event.level)
    {
        case LogLevel::INFO:
            return format_info(event);

        case LogLevel::ERROR:
            return format_error(event);

        case LogLevel::DEBUG:
            return format_debug(event);
    }

    return "";
}

const char* Formatter::filename(const char* path) {
    const char* slash = std::strrchr(path, '/');
    return slash ? slash + 1 : path;
}

std::string Formatter::format_info(const LogEvent& event) {
    return "[" + event.timestamp + "] [INFO ] " + event.message;
}

std::string Formatter::format_error(const LogEvent& event) {
    return "[" + event.timestamp + "] [ERROR] " + event.message;
}

std::string Formatter::format_debug(const LogEvent& event)
{
    const char* file = filename(event.file);

    return "[" + event.timestamp + "] [DEBUG] "
           + std::string(file) + ":"
           + std::to_string(event.line)
           + " " + event.function
           + " -> "
           + event.message;
}
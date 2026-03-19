#pragma once

#include <string>

#include "logger/log_event.hpp"

class Formatter
{
public:
    std::string format(const LogEvent& event);

private:
    static const char* filename(const char* path);

    std::string format_info(const LogEvent& event);
    std::string format_error(const LogEvent& event);
    std::string format_debug(const LogEvent& event);
};
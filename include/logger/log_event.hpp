#pragma once

#include <string>

#include "log_level.hpp"

struct LogEvent
{
    /**
     * для всех
     */
    std::string timestamp;
    LogLevel level;
    std::string message;

    /**
     * только для debug
     */
    const char* file;
    int line;
    const char* function;

    LogEvent(const std::string& ts,
             LogLevel lvl,
             const std::string& msg,
             const char* f = "",
             int l = 0,
             const char* func = "")
        :
        timestamp(ts),
        level(lvl),
        message(msg),
        file(f),
        line(l),
        function(func)
    {}
};
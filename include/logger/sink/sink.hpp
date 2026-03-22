#pragma once

#include "logger/log_event.hpp"

class Sink
{
public:
    explicit Sink(std::optional<LogLevel> filter_level = std::nullopt)
    : 
        _filter_level(filter_level) 
    {}
    
    virtual ~Sink() = default;

    virtual void write(const LogEvent& event) = 0;

protected:
    bool should_write(const LogEvent& event) const {
        return !_filter_level.has_value() || event.level == *_filter_level;
    }

protected:
    std::optional<LogLevel> _filter_level;
};
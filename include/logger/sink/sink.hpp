#pragma once

#include "logger/log_event.hpp"

class Sink
{
public:
    virtual ~Sink() = default;

    virtual void write(const LogEvent& event) = 0;
};
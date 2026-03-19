#pragma once

#include <iostream>
#include <memory>

#include "sink.hpp"
#include "logger/formatter/formatter.hpp"

class ConsoleSink : public Sink
{
public:
    void write(const LogEvent& event) override;

private:
    Formatter _formatter;
};
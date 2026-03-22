#pragma once

#include <iostream>
#include <memory>
#include <optional>

#include "sink.hpp"
#include "logger/formatter/formatter.hpp"

class ConsoleSink : public Sink
{
public:
    explicit ConsoleSink(std::optional<LogLevel> filter_level = std::nullopt);

    void write(const LogEvent& event) override;

private:
    Formatter _formatter;
};
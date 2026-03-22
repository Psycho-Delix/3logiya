#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <optional>

#include "sink.hpp"
#include "logger/formatter/formatter.hpp"

class FileSink : public Sink
{
public:
    FileSink(const std::string& path,
             std::optional<LogLevel> filter_level = std::nullopt);
    ~FileSink();

    void write(const LogEvent& event) override;

private:
    std::ofstream _file;
    Formatter _formatter;
};
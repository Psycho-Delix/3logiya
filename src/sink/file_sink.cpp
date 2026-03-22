#include "logger/sink/file_sink.hpp"

FileSink::FileSink(const std::string& path, std::optional<LogLevel> filter_level)
: 
    Sink(filter_level)
{
    _file.open(path, std::ios::app);
}

FileSink::~FileSink() {
    if (_file.is_open()) {
        _file.close();
    }
}

void FileSink::write(const LogEvent& event) {
    if (!should_write(event)) {
        return;
    }
    
    _file << _formatter.format(event) << std::endl;
}
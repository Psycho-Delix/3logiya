#include "logger/sink/file_sink.hpp"

FileSink::FileSink(const std::string& path) {
    _file.open(path, std::ios::app);
}

FileSink::~FileSink() {
    if (_file.is_open()) {
        _file.close();
    }
}

void FileSink::write(const LogEvent& event) {
    _file << _formatter.format(event) << std::endl;
}
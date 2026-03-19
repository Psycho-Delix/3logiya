#include "logger/sink/console_sink.hpp"

void ConsoleSink::write(const LogEvent& event) {
    std::string color;
    switch(event.level) {
        case LogLevel::INFO:  color = "\033[32m"; break;
        case LogLevel::ERROR: color = "\033[31m"; break;
        case LogLevel::DEBUG: color = "\033[34m"; break;
    }
    std::cout << color 
              << _formatter.format(event) 
              << "\033[0m" 
              << std::endl;
}
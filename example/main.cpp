#include "logger/logger.hpp"

int main() {
    auto& logger = Logger::create()
        .to_console()
        .to_file("test.log", LogLevel::INFO);

    LOG_INFO("INFO");
    LOG_DEBUG("DEBUG");
    LOG_ERROR("ERROR");
}
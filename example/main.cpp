#include <iostream>

#include "logger/logger.hpp"

int main() {
    std::cout << "\n";

    auto& logger = Logger::create() 
        .to_console()
        .to_file("text.log");

    logger.info("message");
    logger.error("message");
    
    LOG_INFO("message"); 
    LOG_INFO("message"); 
    LOG_INFO("message"); 
    LOG_ERROR("message");
    LOG_ERROR("message");
    LOG_ERROR("message");
    LOG_ERROR("message");
    LOG_DEBUG("message");
    LOG_DEBUG("message");
    LOG_DEBUG("message");
    LOG_DEBUG("message");
    
    return 0;
}

#include <iostream>

#include "logger/logger.hpp"

struct Point
{
    int x;
    int y;

    std::string to_string() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

int main() {
    std::cout << "\n";

    auto& logger = Logger::create()
        .to_console();

    Point p1{10, 15};
    
    LOG_DEBUG("Pont: {}", p1.to_string()); 
    
    return 0;
}

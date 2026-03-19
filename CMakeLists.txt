cmake_minimum_required(VERSION 3.16)
project(3logiya VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB LOGGER_HEADERS
        "include/logger/*.hpp"
        "include/logger/sink/*.hpp"
        "include/logger/formatter/*.hpp"
    )

file(GLOB LOGGER_SOURCES
        "src/*.cpp"
        "src/sink/*.cpp"
        "src/formatter/*.cpp"
    )

add_library(logger STATIC ${LOGGER_SOURCES} ${LOGGER_HEADERS})

target_include_directories(logger PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(3logiya example/main.cpp)
target_link_libraries(3logiya PRIVATE logger)

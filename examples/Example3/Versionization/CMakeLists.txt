cmake_minimum_required(VERSION 3.10)
project(example3 VERSION 1.0.0)

configure_file(config.h.in config.h)

add_executable(example3 main.cpp)

target_include_directories(example3 PUBLIC
    ${CMAKE_BINARY_DIR}
)

option(ENABLE_LOGGING "Enable logging support" ON)

if(ENABLE_LOGGING)
    target_compile_definitions(example3 PRIVATE ENABLE_LOGGING)
endif()

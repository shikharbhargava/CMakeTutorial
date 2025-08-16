cmake_minimum_required(VERSION 3.10)
project(example2)

add_subdirectory(hello)
add_subdirectory(math)
add_subdirectory(logger)

add_executable(example2 main.cpp)

target_link_libraries(example2 PRIVATE hello math logger)

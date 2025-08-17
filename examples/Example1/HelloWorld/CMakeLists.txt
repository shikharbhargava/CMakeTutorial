# Example1/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(example1)

# Create main executable
add_executable(example1
    main.cpp
    hello/src/hello.cpp
)
target_include_directories(example1 PUBLIC hello/include)

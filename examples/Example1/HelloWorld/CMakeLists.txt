# MyProject/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(example1)

add_subdirectory(hello)

# Create main executable
add_executable(example1
    main.cpp
)

# Link library to the main target
target_link_libraries(example1 PRIVATE hello)

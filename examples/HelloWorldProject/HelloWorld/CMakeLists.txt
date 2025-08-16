# MyProject/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyProject)

include_directories(hello)

# Create main executable
add_executable(MyProject
    main.cpp
)

# Link library to the main target
target_link_libraries(MyProject PRIVATE hello)

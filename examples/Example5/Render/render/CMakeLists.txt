add_library(render src/render.cpp)

target_include_directories(render PUBLIC include ${OpenCV_INCLUDE_DIRS})
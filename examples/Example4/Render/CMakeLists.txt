cmake_minimum_required(VERSION 3.10)
# Compiler flags
if (UNIX)
  include(cmake/CompilerFlags.cmake)
endif()

project(Render)

if(DEFINED ENV{OPENCV_INSTALL})
  set(OPENCV_PATH $ENV{OPENCV_INSTALL})
  message(STATUS "Found OPENCV PATH from environment variable OPENCV_INSTALL: " ${OPENCV_PATH})
  # if linux
  if(UNIX)
    set(OpenCV_DIR "${OPENCV_PATH}/lib/cmake/opencv4")
  else()
    set(OpenCV_DIR "${OPENCV_PATH}/build")
  endif()
endif()

find_package(OpenCV REQUIRED)

# Option to enable BLACK_AND_WHITE mode
option(BLACK_AND_WHITE "Render images in grayscale" OFF)

add_subdirectory(ArgParser)
add_subdirectory(render)
add_subdirectory(json)
add_subdirectory(utils)

add_executable(Render main.cpp)

target_link_libraries(Render PRIVATE utils ArgParser render json ${OpenCV_LIBS})

if(BLACK_AND_WHITE)
    target_compile_definitions(render PUBLIC BLACK_AND_WHITE)
endif()

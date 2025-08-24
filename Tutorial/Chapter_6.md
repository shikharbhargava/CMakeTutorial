# Chapter 6: Finding and Linking External Dependencies
<p align="right">
  <a href="Chapter_5.md"><b><< Previous</b></a>
  <b>&nbsp;</b>
  [
  <a href="Chapter_1.md">1</a>,
  <a href="Chapter_2.md">2</a>,
  <a href="Chapter_3.md">3</a>,
  <a href="Chapter_4.md">4</a>,
  <a href="Chapter_5.md">5</a>,
  <b>6</b>,
  <a href="Chapter_7.md">7</a>,
  <a href="Chapter_8.md">8</a>,
  <a href="Chapter_9.md">9</a>,
  <a href="Chapter_10.md">10</a>
  ]
  <b>&nbsp;</b>
  <a href="Chapter_7.md"><b>Next >></b></a>
</p>
<p align="center">
  <img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" alt="CMake Logo" width="60"/>
</p>

---

## 📂 Step 1: Why External Dependencies Matter

Most real-world projects depend on external libraries (Boost, OpenCV, SDL, etc.). CMake provides mechanisms to **find, configure, and link external dependencies** in a cross-platform way.

---

## ⚙️ Step 2: Finding a Package

CMake uses the command `find_package()` to locate and configure external libraries.

Example:

```cmake
find_package(OpenCV REQUIRED)

add_executable(example4 main.cpp)
target_link_libraries(example4 PRIVATE ${OpenCV_LIBS})
```

📌 Requirements for a package to be searchable:

* A **Find Module** file (`Find<Package>.cmake`) must exist in CMake’s module path, OR
* The package must provide a **Config file** (`<Package>Config.cmake` or `<lowercase>-config.cmake`)
* The location of these files must be known to CMake (via `CMAKE_MODULE_PATH` or system paths)

---

## 📑 Step 3: Variables Created by `find_package()`

When a package is found, CMake sets useful variables (these vary by package, but common ones include):

* `<Package>_FOUND` → `TRUE` if the package is found
* `<Package>_INCLUDE_DIRS` → Paths to include directories
* `<Package>_LIBRARIES` → Full paths or names of libraries
* `<Package>_LIBRARY_DIRS` → Paths to library directories
* `<Package>_VERSION` → Version string (if provided)
* `<Package>_DEFINITIONS` → Compiler definitions required

Example for OpenCV:

```cmake
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV Include: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV Libs: ${OpenCV_LIBS}")
```

---

## 📂 Step 4: Linking External Packages

```cmake
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(example4 main.cpp)
target_link_libraries(example4 PRIVATE ${OpenCV_LIBS})
```

📌 This ensures:

* Your code can `#include <opencv2/...>`
* The correct OpenCV libraries are linked automatically

---

## 🔄 Step 5: Handling Multiple Installations of a Package

Sometimes a system has **multiple versions of a library** installed (e.g., OpenCV 3.x and 4.x). To control which one CMake picks:

### Option 1: Use Environment Variables

```bash
export OpenCV_DIR=/path/to/specific/opencv/build
```

CMake will look for `OpenCVConfig.cmake` in this directory.

```cmake
find_package(OpenCV REQUIRED)
```

### Option 2: Override CMake Variables

```bash
cmake -DOpenCV_DIR=/path/to/specific/opencv/build ..
```

This sets the CMake variable directly.

### Option 3: Set `CMAKE_PREFIX_PATH`

```bash
cmake -DCMAKE_PREFIX_PATH="/path/to/opencv/install" ..
```

CMake will search this path when looking for config files.

---

## ⚡ Step 6: Why This Matters

* Ensures reproducible builds when multiple library versions exist
* Makes builds portable across different environments
* Avoids accidental linking against the wrong system library

---

👉 **Takeaway:** Use `find_package()` with care, and guide CMake with environment variables or `CMAKE_PREFIX_PATH` when multiple installations exist.

---

✅ **Pro Tip:** Always check `<Package>_INCLUDE_DIRS` and `<Package>_LIBRARIES` with `message(STATUS ...)` to confirm CMake found the expected version.

---

## 📂 Step 7: Example4 — Render Project

To make things concrete, let’s design **Example4: Render**.

**Folder Layout:**

```
Example4/Render
├── CMakeLists.txt
├── render/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── render.h
│   └── src/
│       └── render.cpp
├── json/
│   ├── CMakeLists.txt
│   └── include/
│       └── nlohmann/json.hpp   (header-only library)
└── main.cpp
```

**Project Features:**

* Library `render` that uses **OpenCV** to display images.
* Header-only library `json` using **nlohmann/json** bundled in the project.
* `main.cpp` reads a JSON file containing a list of image paths, then calls `render`.
* A **compile-time macro** `BLACK_AND_WHITE`:

  * Controlled via `option(BLACK_AND_WHITE ...)` in CMake.
  * If set, the render library converts images to grayscale before displaying.

👉 This example shows how to combine:

* External dependencies (OpenCV)
* Internal header-only libraries (nlohmann/json)
* Feature toggles via compile-time macros

---

## ⚙️ Top-level `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)
project(Render)

find_package(OpenCV REQUIRED)

# Option to enable BLACK_AND_WHITE mode
option(BLACK_AND_WHITE "Render images in grayscale" OFF)

add_subdirectory(render)
add_subdirectory(json)

add_executable(Render main.cpp)

target_link_libraries(Render PRIVATE render json ${OpenCV_LIBS})

if(BLACK_AND_WHITE)
    target_compile_definitions(render PUBLIC BLACK_AND_WHITE)
endif()
```

---

## ⚙️ `render/CMakeLists.txt`

```cmake
add_library(render src/render.cpp)

target_include_directories(render PUBLIC include ${OpenCV_INCLUDE_DIRS})
```

---

## ⚙️ `json/CMakeLists.txt`

```cmake
add_library(json INTERFACE)

target_include_directories(json INTERFACE include)
```

---

## 📄 `render/include/render.h`

```cpp
#pragma once
#include <string>
#include <vector>

namespace render {
    void display_images(const std::vector<std::string>& image_paths);
}
```

---

## 📄 `render/src/render.cpp`

```cpp
#include "render.h"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace render {
    void display_images(const std::vector<std::string>& image_paths) {
        for (const auto& path : image_paths) {
            cv::Mat img = cv::imread(path);
            if (img.empty()) {
                std::cerr << "Failed to load: " << path << std::endl;
                continue;
            }

#ifdef BLACK_AND_WHITE
            cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
#endif

            cv::imshow("Render", img);
            cv::waitKey(0);
        }
    }
}
```

---

## 📄 `main.cpp`

```cpp
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "render.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: Render <images.json>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    nlohmann::json j;
    file >> j;

    std::vector<std::string> image_paths = j["images"].get<std::vector<std::string>>();

    render::display_images(image_paths);

    return 0;
}
```

---
## 📄 images.json (sample input)

```json
{
  "images": [
    "image1.jpg",
    "image2.jpg",
    "image3.png"
  ]
}
```

---

## 🛠️ Build and Run Example
```
mkdir build && cd build
cmake .. -DBLACK_AND_WHITE=ON
make
./Render ../images.json
```

---

✅ This example ties everything together:

* `render` library handles image display
* `json` is a bundled header-only dependency
* `main.cpp` glues them together
* The compile-time macro `BLACK_AND_WHITE` toggles grayscale rendering

---

> ➡️ [**Next:**](Chapter_7.md) Chapter 7: Installing the Project
<p align="right">
  <a href="Chapter_5.md"><b><< Previous</b></a>
  <b>&nbsp;</b>
  [
  <a href="Chapter_1.md">1</a>,
  <a href="Chapter_2.md">2</a>,
  <a href="Chapter_3.md">3</a>,
  <a href="Chapter_4.md">4</a>,
  <a href="Chapter_5.md">5</a>,
  <b>6</b>,
  <a href="Chapter_7.md">7</a>,
  <a href="Chapter_8.md">8</a>,
  <a href="Chapter_9.md">9</a>,
  <a href="Chapter_10.md">10</a>
  ]
  <b>&nbsp;</b>
  <a href="Chapter_7.md"><b>Next >></b></a>
</p>

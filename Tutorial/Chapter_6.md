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

> [**Next:**](Chapter_7.md) Installing the Project
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

# Chapter 5: Project Configuration and Versioning
<p align="right">
  [
  <a href="Chapter_1.md">1</a>,
  <a href="Chapter_2.md">2</a>,
  <a href="Chapter_3.md">3</a>,
  <a href="Chapter_4.md">4</a>,
  <b>5</b>,
  <a href="Chapter_6.md">6</a>,
  <a href="Chapter_7.md">7</a>,
  <a href="Chapter_8.md">8</a>,
  <a href="Chapter_9.md">9</a>,
  <a href="Chapter_10.md">10</a>
  ]
  <b>&nbsp;&nbsp;</b>
  <a href="Chapter_6.md"><b>Next >></b></a>
</p>
<p align="center">
  <img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" alt="CMake Logo" width="60"/>
</p>

In this chapter, we’ll learn how to **add project versioning and configuration options** to your CMake project. You’ll see how to:

* Define project versions (major, minor, patch)
* Generate a configuration header file with version info
* Control features with build-time options
* Inspect example build outputs

This makes your project **version-aware, flexible, and maintainable** as it grows.

---

## 📂 Step 1: Project Structure and Version

**Example3 Folder Layout:**

```
Example3/Versionization/
├── CMakeLists.txt
├── config.h.in
└── main.cpp
```

---

## 📂 Step 2: Setting Project Version

CMake allows you to specify a project version directly in your `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.10)
project(example3 VERSION 1.2.3)

add_executable(example3 main.cpp)
```

📌 This tells CMake:

* The folder is named **Example3**
* The project is named **example3**
* The project version is **1.2.3**
* Variables created:

  * `PROJECT_VERSION` → `1.2.3`
  * `PROJECT_VERSION_MAJOR` → `1`
  * `PROJECT_VERSION_MINOR` → `2`
  * `PROJECT_VERSION_PATCH` → `3`

---

## 📝 Step 2: Configuring a Header File

It’s common to generate a header file with version info that your code can use.

Create a template file `config.h.in`:

```cpp
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define PROJECT_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define PROJECT_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define PROJECT_VERSION_PATCH @PROJECT_VERSION_PATCH@

#endif // _CONFIG_H_
```

Update `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(example3 VERSION 1.2.3)

configure_file(config.h.in config.h)

add_executable(example3 main.cpp)

target_include_directories(example3 PUBLIC
    ${CMAKE_BINARY_DIR}
)
```

📌 This tells CMake:

* `configure_file` replaces placeholders (`@VAR@`) with actual values
* Generates `config.h` inside your build directory
* Adds build directory to include path so `#include "config.h"` works

---

## ⚡ Step 3: Using Version Info in Code

```cpp
#include <iostream>
#include "config.h"

int main() {
    std::cout << "Project Version: "
              << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "."
              << PROJECT_VERSION_PATCH << std::endl;
    return 0;
}
```

---

## ⚙️ Step 4: Setting Options for Features

You can provide build options for enabling/disabling features.

```cmake
option(ENABLE_LOGGING "Enable logging support" ON)

if(ENABLE_LOGGING)
    target_compile_definitions(example3 PRIVATE ENABLE_LOGGING)
endif()
```

Code example:

```cpp
#include <iostream>

int main() {
#ifdef ENABLE_LOGGING
    std::cout << "Logging is enabled!" << std::endl;
#else
    std::cout << "Logging is disabled." << std::endl;
#endif
    return 0;
}
```

Build with logging disabled:

```bash
cmake .. -DENABLE_LOGGING=OFF
```

---

## ⚡ Step 5: Example Build Output

When building `example3`, you may see output like this:

```
-- Configuring done
-- Generating done
-- Build files have been written to: /path/to/Example3/build
[100%] Building CXX object CMakeFiles/example3.dir/main.cpp.o
[100%] Linking CXX executable example3
```

---

## ⚡ Step 6: Why Configuration Matters

* Embed **version numbers** into binaries
* Enable/disable **optional features**
* Keep builds **flexible and reusable**
* Provide **clear build-time choices**

---

👉 **Takeaway:** Project configuration in CMake makes your build system adaptable, version-aware, and easier to maintain.

---

✅ **Pro Tip:** Use `configure_file` and `option()` to keep your builds flexible and avoid hardcoding values.

---

> [**Next:**](Chapter_6.md) Optional Features and Testing
<p align="right">
  [
  <a href="Chapter_1.md">1</a>,
  <a href="Chapter_2.md">2</a>,
  <a href="Chapter_3.md">3</a>,
  <a href="Chapter_4.md">4</a>,
  <b>5</b>,
  <a href="Chapter_6.md">6</a>,
  <a href="Chapter_7.md">7</a>,
  <a href="Chapter_8.md">8</a>,
  <a href="Chapter_9.md">9</a>,
  <a href="Chapter_10.md">10</a>
  ]
  <b>&nbsp;&nbsp;</b>
  <a href="Chapter_6.md"><b>Next >></b></a>
</p>

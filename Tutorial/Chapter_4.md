# Chapter 4: Libraries, subdirectories, and making CMake project scale.
<p align="right">
  [
  <a href="Chapter_1.md">1</a>,
  <a href="Chapter_2.md">2</a>,
  <a href="Chapter_3.md">3</a>,
  <b>4</b>,
  <a href="Chapter_5.md">5</a>,
  <a href="Chapter_6.md">6</a>,
  <a href="Chapter_7.md">7</a>,
  <a href="Chapter_8.md">8</a>,
  <a href="Chapter_9.md">9</a>,
  <a href="Chapter_10.md">10</a>
  ]
  <b>&nbsp;&nbsp;</b>
  <a href="Chapter_5.md"><b>Next >></b></a>
</p>

<p align="center">
  <img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" alt="CMake Logo" width="60"/>
</p>

---

## 📂 Step 1: Scaling Project Structure

As projects grow, you’ll often have **multiple libraries** and separate subdirectories. CMake makes it easy to organize and scale.

**Example Project Layout (with CMakeLists.txt at each level):**

```
Example2/HelloWorld/
├── CMakeLists.txt
│
├── hello/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── hello.h
│   └── src/
│       └── hello.cpp
│
├── math/
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── math_utils.h
│   └── src/
│       └── math_utils.cpp
│
├── logger/
│   ├── CMakeLists.txt
│   └── include/
│       └── logger.h
│
└── main.cpp
```

---

## 📝 Step 1.1: Example Code

```cpp
// math/include/math_utils.h
#ifndef _MATH_UTILS_H_
#define _MATH_UTILS_H_

int add(int a, int b);

#endif // _MATH_UTILS_H_
```

```cpp
// math/src/math_utils.cpp
#include "math_utils.h"
int add(int a, int b)
{
  return a + b;
}
```

```cpp
// logger/include/logger.h
#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>

inline void logMessage(const std::string& msg)
{
  std::cout << "[LOG] " << msg << std::endl;
}

#endif // _LOGGER_H_
```

```cpp
// main.cpp
#include <iostream>
#include "hello.h"
#include "math_utils.h"
#include "logger.h"

int main()
{
  std::cout << getMessage() << "\\n";
  std::cout << "2 + 3 = " << add(2, 3) << std::endl;
  logMessage("Main function executed successfully");
  return 0;
}
```

---

## ⚙️ Step 2: Using Subdirectories in CMake

Top-level `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(example2)

add_subdirectory(hello)
add_subdirectory(math)
add_subdirectory(logger)

add_executable(example2 main.cpp)

target_link_libraries(example2 PRIVATE hello math logger)
```

Library `CMakeLists.txt` inside `hello/`:

```cmake
add_library(hello STATIC src/hello.cpp)

target_include_directories(hello PUBLIC include)
```

Library `CMakeLists.txt` inside `math/`:

```cmake
add_library(math STATIC src/math_utils.cpp)

target_include_directories(math PUBLIC include)
```

Interface library `CMakeLists.txt` inside `logger/`:

```cmake
add_library(logger INTERFACE)

target_include_directories(logger INTERFACE include)
```

📌 This tells CMake:

* Split code into multiple **subdirectories**
* Each subdirectory has its own **CMakeLists.txt**
* Build libraries `hello` and `math`
* Add an **interface library** `logger` that only exposes headers
* Link all of them to the main target

---

## ⚡ Step 3: Configuring and Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

📷 Example build output:

```
[ 25%] Built target hello
[ 50%] Built target math
[ 75%] Built target logger
[100%] Built target example2
```

---

## ⚙️ Step 4: Why Subdirectories Matter

* Keeps code **modular and organized**
* Makes it easier to **reuse components**
* Scales well for **large projects**
* Allows separate **testing and installation rules** for each module
* Supports **interface libraries** for header-only utilities

---

👉 **Takeaway:** Subdirectories let you split your project into manageable pieces. Each library can evolve independently while staying part of the main build.

---

✅ **Pro Tip:** Every individual library should have its own `CMakeLists.txt` file inside its folder. This keeps responsibilities clear and allows each module to define its own sources, include paths, and build rules.

---

> [**Next:**](Chapter_5.md) Project Configuration and Versioning

<p align="right">
  [
  <a href="Chapter_1.md">1</a>,
  <a href="Chapter_2.md">2</a>,
  <a href="Chapter_3.md">3</a>,
  <b>4</b>,
  <a href="Chapter_5.md">5</a>,
  <a href="Chapter_6.md">6</a>,
  <a href="Chapter_7.md">7</a>,
  <a href="Chapter_8.md">8</a>,
  <a href="Chapter_9.md">9</a>,
  <a href="Chapter_10.md">10</a>
  ]
  <b>&nbsp;&nbsp;</b>
  <a href="Chapter_5.md"><b>Next >></b></a>
</p>
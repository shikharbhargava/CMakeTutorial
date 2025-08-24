# Chapter 7: Installing the Project

<p align="center">
  <img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" alt="CMake Logo" width="60"/>
</p>

---

## 📂 Step 1: Why Installation Matters

When you build a project, the resulting binaries remain in the **build tree**. But for **distribution or reuse**, you need to install them into a standard location controlled by `CMAKE_INSTALL_PREFIX` (default: `/usr/local` on Linux, `C:/Program Files` on Windows).

Installation in CMake ensures:

* Executables and libraries are placed in proper directories under the prefix
* Runtime dependencies are bundled for portability
* The folder can be made **self-contained**
* Packaging tools (like CPack) can create installable archives

---

## ⚙️ Step 2: Installing Executables and Libraries

In your `CMakeLists.txt` you can specify what to install:

```cmake
# Install library into ${CMAKE_INSTALL_PREFIX}/lib
install(TARGETS render
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
)

# Install executable into ${CMAKE_INSTALL_PREFIX}/bin
install(TARGETS Render
    RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
)
```

📌 This tells CMake:

* Place your `render` library inside `lib/`
* Place your `Render` executable inside `bin/`

---

## 📄 Step 3: Installing Dependencies Automatically

To make the install tree portable, you can let CMake detect runtime dependencies of your target and copy them:

```cmake
install(CODE "
    file(GET_RUNTIME_DEPENDENCIES
        RESOLVED_DEPENDENCIES_VAR deps
        EXECUTABLES $<TARGET_FILE:Render>
        PRE_INCLUDE_REGEXES ".*"
        POST_INCLUDE_REGEXES ".*"
    )
    foreach(dep ${deps})
        file(INSTALL DESTINATION \"${CMAKE_INSTALL_PREFIX}/lib\" TYPE SHARED_LIBRARY FILES \"${dep}\")
    endforeach()
")
```

📌 This copies non-system runtime dependencies (like OpenCV `.so`/`.dll`) into the `${CMAKE_INSTALL_PREFIX}/lib` folder. Native C++ runtimes are skipped. This makes your install tree portable and self-sufficient.

---

## 📊 Step 4: Source → Build → Install Flow

```
Source Tree              Build Tree                Install Tree
-----------              ----------                ------------
Example4/                build/                    ${CMAKE_INSTALL_PREFIX}/
├── CMakeLists.txt  →    CMakeCache.txt       →    bin/Render
├── render/         →    render/CMakeFiles/   →    lib/librender.a + libopencv*.so
└── main.cpp      →    CMakeFiles/Render.dir   →    
```

📌 **Flow:**

* Source files → compiled objects in build tree → installed executable and libraries
* External dependencies installed alongside project (unless system-provided)

---

## 💻 Step 5: Platform Differences

### Linux (default)

* Default install prefix: `/usr/local`
* Override with:

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/myportableapp
make install
```

Installs into `$HOME/myportableapp/bin`, `$HOME/myportableapp/lib`, etc.

You can also stage installs with `DESTDIR`:

```bash
make install DESTDIR=$PWD/staging
```

This installs into `staging/usr/local/...`

### Windows

* Default install prefix: `C:/Program Files (x86)/<Project>`
* Override with:

```powershell
cmake .. -DCMAKE_INSTALL_PREFIX=C:/Users/YourName/myportableapp
cmake --build . --target install
```

Installs into `C:/Users/YourName/myportableapp/bin`, `.../lib`, etc.

📌 On Windows, `.dll` dependencies are often placed in `bin/` so the `.exe` can find them directly.

---

👉 **Takeaway:** Use `install()` for both executables and libraries, copy runtime dependencies automatically, and control installation with `CMAKE_INSTALL_PREFIX`. This ensures your project is portable, relocatable, and ready for packaging.

---

## 📝 CMakeLists.txt Example

Here is a minimal example you can add to your attached **Render** project to enable installation of both the library and executable:

```cmake
cmake_minimum_required(VERSION 3.16)
project(Render)

find_package(OpenCV REQUIRED)
find_package(nlohmann_json REQUIRED)

# Library target
add_library(render render/src/hello.cpp)
target_include_directories(render PUBLIC render/include)

# Executable target
add_executable(Render main.cpp)

# Link libraries
target_link_libraries(Render PRIVATE render ${OpenCV_LIBS} nlohmann_json::nlohmann_json)

# Install library into ${CMAKE_INSTALL_PREFIX}/lib
install(TARGETS render
    ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
    LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib"
)

# Install executable into ${CMAKE_INSTALL_PREFIX}/bin
install(TARGETS Render
    RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin"
)

# Install runtime dependencies
install(CODE "
    file(GET_RUNTIME_DEPENDENCIES
        RESOLVED_DEPENDENCIES_VAR deps
        EXECUTABLES $<TARGET_FILE:Render>
        PRE_INCLUDE_REGEXES ".*"
        POST_INCLUDE_REGEXES ".*"
    )
    foreach(dep ${deps})
        file(INSTALL DESTINATION \"${CMAKE_INSTALL_PREFIX}/lib\" TYPE SHARED_LIBRARY FILES \"${dep}\")
    endforeach()
")
```

📌 With this, you can run:

```bash
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=$HOME/myportableapp
cmake --build build --target install
```

This installs:

* `Render` executable into `$HOME/myportableapp/bin`
* `librender.a` (or `.so`) into `$HOME/myportableapp/lib`
* runtime dependencies (like OpenCV) into `$HOME/myportableapp/lib`

On Windows, use the PowerShell commands described above.

---

## 🔄 Switching from Static to Shared Library

By default, CMake builds `render` as a static library (`librender.a`). To make it a dynamic/shared library (`librender.so` on Linux, `render.dll` on Windows), update the declaration:

```cmake
# Before:
add_library(render src/render.cpp)

# After (shared library):
add_library(render SHARED src/render.cpp)

# Keep include directories
target_include_directories(render PUBLIC include ${OpenCV_INCLUDE_DIRS})
```

📌 Why this matters:

* A static library is bundled directly into the executable, no need to install separately.
* A shared library must be installed and available at runtime, justifying installation rules.
* This change makes `render` part of the runtime environment and ensures it is copied into `${CMAKE_INSTALL_PREFIX}/lib`.

---

> ➡️ [**Next:**](Chapter_8.md) Chapter 8: Creating Installable Packages

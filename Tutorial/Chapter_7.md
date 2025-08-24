# Chapter 7: Installing the Project

<p align="center">
  <img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" alt="CMake Logo" width="60"/>
</p>

---

## 📂 Step 1: Why Installation Matters

When you build a project, the resulting binaries remain in the build tree. But for **distribution or reuse**, you need to install them into a standard location (like `/usr/local` on Linux or `C:/Program Files` on Windows).

Installation in CMake ensures:

* Executables are placed in proper system directories
* Runtime dependencies are bundled for portability
* The folder can be made **self‑contained**
* Packaging tools (like CPack) can create installable archives

---

## ⚙️ Step 2: Installing Executables

In your `CMakeLists.txt` you can specify what to install:

```cmake
# Install executable
install(TARGETS Render
    RUNTIME DESTINATION bin
)
```

📌 This tells CMake:

* Place the executable in `bin/`

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

📌 This copies non‑system runtime dependencies (like OpenCV `.so`/`.dll`) into the `lib/` folder under your install prefix. Native C++ runtimes are skipped. This makes your install tree portable and self‑sufficient.

---

## 📊 Step 4: Source → Build → Install Flow

```
Source Tree              Build Tree                Install Tree
-----------              ----------                ------------
Example4/                build/                    /usr/local/
├── CMakeLists.txt  →    CMakeCache.txt       →    bin/Render
├── render/         →    render/CMakeFiles/   →    lib/libopencv*.so
└── main.cpp      →    CMakeFiles/Render.dir   →    
```

📌 **Flow:**

* Source files → compiled objects in build tree → installed executable and runtime libraries
* External dependencies installed alongside project (unless system-provided)

---

## 💻 Step 5: Platform Differences

### Using `CMAKE_INSTALL_PREFIX`

* Controls where your project is installed
* Linux default: `/usr/local`
* Windows default: `C:/Program Files (x86)/<Project>`

Override at configure time:

```bash
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/myportableapp
make install
```

Installs into `$HOME/myportableapp/bin`, `$HOME/myportableapp/lib`, etc.

On Windows:

```powershell
cmake .. -DCMAKE_INSTALL_PREFIX=C:/Users/YourName/myportableapp
cmake --build . --target install
```

Installs into `C:/Users/YourName/myportableapp/bin`, `.../lib`, etc.

---

👉 **Takeaway:** Define install rules for executables and runtime dependencies, use `CMAKE_INSTALL_PREFIX` to control install location, and make your project portable and ready for packaging.

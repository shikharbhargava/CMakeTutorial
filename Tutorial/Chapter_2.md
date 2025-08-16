# Chapter 2: Why Use CMake Instead of Makefiles?
<p align="right">
<span >[</span>
<a ref="Chapter_1">1</a>
<span >,</span>
<span >2</span>
<span >,</span>
<a ref="Chapter_3">3</a>
<span >,</span>
<a ref="Chapter_4">4</a>
<span >,</span>
<a ref="Chapter_5">5</a>
<span >,</span>
<a ref="Chapter_6">6</a>
<span >,</span>
<a ref="Chapter_7">7</a>
<span >,</span>
<a ref="Chapter_5">8</a>
<span >,</span>
<a ref="Chapter_9">9</a>
<span >,</span>
<a ref="Chapter_10">10</a>
<span >]</span>
<a ref="Chapter_3"><b>&nbsp;&nbsp;Next >></b></a>
</p>
<p align="center">
    <img src="https://cmake.org/wp-content/uploads/2023/08/CMake-Mark-1.svg" alt="CMake Logo" width="60" style="vertical-align:middle;"/>
    <span style="display:inline-block; font-size:1.5em; font-weight:bold; margin: 0 16px; vertical-align:middle; line-height:60px;">vs</span>
    <img src="https://upload.wikimedia.org/wikipedia/commons/8/83/The_GNU_logo.png" alt="GNU Make Logo" width="60" style="vertical-align:middle;"/>
</p>

---

## 🔎 Makefiles vs. CMake

- **Makefiles** — describe build steps for the `make` tool in a platform-specific format.
- **CMake** — generates build files for **any** supported platform or toolchain (including Makefiles), from a single source (`CMakeLists.txt`).

---

## 🚩 Limitations of Makefiles

- 📝 **Manual and error-prone** for large projects  
- ❌ No native cross-platform support  
- 🛠️ Harder to integrate with IDEs and new build tools  
- 🔄 No built-in configuration management or feature toggles  
- ⚠️ Maintenance complexity grows exponentially  
- 🔗 Dependencies (headers, libraries) must be manually managed  
- 📂 Include directories must be updated manually in every build rule

---

## 🪄 Advantages of CMake

- 🌍 **Cross-platform by design**  
  Write once, generate for any OS or IDE.
- 📦 **Generates build files automatically**  
  (Make, Ninja, Visual Studio, Xcode…)
- 🧩 **Supports modular project structures**  
  Out-of-source builds, subprojects, libraries, tests.
- 🔧 **Easy configuration management**  
  `option()`, `configure_file()`, feature flags.
- 💻 **Deep IDE integration**  
  Works with VSCode, Visual Studio, CLion, Qt Creator, and more.
- 🛡️ **Dependency management**  
  `find_package()`, `FetchContent`, external projects.
- ⛓️ **Automatic rebuilds on header changes**  
  No need to manually list dependencies.
- 📂 **Smart include path handling**  
  `target_include_directories()` keeps it clean.

---

## ✨ Example: Same Project in Makefile vs. CMake

**Makefile**
```make
CC=g++
CFLAGS=-I.
DEPS = MathFunctions.h
OBJ = tutorial.o MathFunctions.o

tutorial: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
```

**CMakeLists.txt**
```cmake
cmake_minimum_required(VERSION 3.10)
project(Tutorial)

add_executable(Tutorial tutorial.cpp)
add_library(MathFunctions MathFunctions.cpp)
target_link_libraries(Tutorial PRIVATE MathFunctions)
```

---

## 💬 Summary

CMake **removes boilerplate**, handles complexity, and keeps your project maintainable as it grows.  
For anything beyond a quick one-file test program — **CMake wins**.

---

> [**Next:**](Chapter_3.md) Setting up your first CMake project.

<p align="right">
<span >[</span>
<a ref="Chapter_1">1</a>
<span >,</span>
<span >2</span>
<span >,</span>
<a ref="Chapter_3">3</a>
<span >,</span>
<a ref="Chapter_4">4</a>
<span >,</span>
<a ref="Chapter_5">5</a>
<span >,</span>
<a ref="Chapter_6">6</a>
<span >,</span>
<a ref="Chapter_7">7</a>
<span >,</span>
<a ref="Chapter_5">8</a>
<span >,</span>
<a ref="Chapter_9">9</a>
<span >,</span>
<a ref="Chapter_10">10</a>
<span >]</span>
<a ref="Chapter_3"><b>&nbsp;&nbsp;Next >></b></a>
</p>
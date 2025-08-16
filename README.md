# CMakeTutorial

Welcome to **CMakeTutorial** — a hands-on guide to understanding and mastering CMake for C and C++ projects. This tutorial walks you through the basics, advantages, and practical usage of CMake, with clear examples and step-by-step chapters.

---

## 📚 Chapters

- [Chapter 1: Introduction to CMake](Chapter_1.md)  
  What is CMake, where is it used, and why should you learn it?

- [Chapter 2: Why Use CMake Instead of Makefiles?](Chapter_2.md)  
  CMake vs. Makefiles, advantages, and a side-by-side example.

- [Chapter 3: Setting Up a CMake Project](Chapter_3.md)  
  Project structure, writing `CMakeLists.txt`, and the build process.

- [Chapter 4: (Coming Soon)](Chapter_4.md)  
  Advanced topics: libraries, subdirectories, scaling up your project.

---

## 🗂️ Examples

- [examples/HelloWorldProject/](examples/HelloWorldProject/)  
  A minimal CMake-based C++ project demonstrating:
  - Modular structure with a library (`hello`)
  - Out-of-source builds
  - Visual Studio and cross-platform support

  **Subfolders:**
  - [`HelloWorld/`](examples/HelloWorldProject/HelloWorld/) — Source code and CMake files
  - [`build/`](examples/HelloWorldProject/build/) — Example build output (Visual Studio, MSVC)

---

## 🛠️ How to Use

1. **Read the chapters in order** for a guided learning experience.
2. **Explore the example projects** in [`examples`](examples/).
3. **Try building the example** yourself:
   ```sh
   cd examples/HelloWorldProject
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

---

## 📖 License

See [LICENSE](LICENSE) for details.

---
# Ghost-Engine
### *A Work-In-Progress C++ game engine*

***

<ins>**Description:**</ins>

Ghost Engine is a **C++17** based game engine which 
uses **OpenGL** as it's rendering API. The project files can be easily generated 
using premake scripts. It supports basic features such as rendering - drawing quads, 
textures, handling input, logging support, ImGui UI panels and viewports. 
Scripts can be written in C++ inside the project itself, and attached to entities.

Right now, this engine has been developed for the **Windows OS only**, with 
**Visual Studio 2019** as the IDE of choice.

***

<ins>**Implemented Features:**</ins>

 * Premake Setup
 * Console Logging
 * Event System and Events
 * LayerStack and Layers
 * Internal Key, Mouse Codes and Input polling
 * Timesteps, Vsync, Delta Time
 * Visual Profiling (uses [Chrome Tracing](chrome://tracing))
 * Modern OpenGL setup, using Glad
 * 2D Rendering pipeline - VertexBuffers, IndexBuffers, VertexArrays
 * ImGui, Docking, Frambuffers and ImGui Viewport
 * Shaders and Textures
 * Simplified API for drawing colored and textured quads.
 * Entity Component System
 * Native C++ scripting
 * ImGui Console Logging
 * ImGui Scene Hierarchy Panel
 * ImGui Properties Panel
 * Scene Serialization and Deserialization using YAML (WIP)

***

<ins>**Cloning:**</ins>

Clone this repository to a local destination using git:  
`git clone --recursive https://github.com/CybernetHacker14/Ghost-Engine`  

***

<ins>**Project Creation:**</ins>

<ins>*Windows-*</ins> Run the `Win-GenProjects.bat` file in `scripts` folder.
This will generate a Visual Studio 2019 solution with appropriate settings.

The `Win-GenProjects.bat` file can also be edited to generate a Visual Studio 2017
solution by changing:  
`call vendor\premake\bin\premake5.exe vs2019` to `call vendor\premake\bin\premake5.exe vs2017`

***

<ins>**Technical Information:**</ins>

<ins>*Supported IDEs:*</ins> 
 * Visual Studio 2017
 * Visual Studio 2019  

<ins>*Languages:*</ins> 
 * C++17 (Core)
 * GLSL (Shader Language)
 * Lua (Premake)

<ins>*External Libraries Used:*</ins> 
 * [GLFW](https://www.glfw.org/)
 * [Glad](https://glad.dav1d.de/)
 * [ImGui](https://github.com/ocornut/imgui)
 * [spdlog](https://github.com/gabime/spdlog)
 * [glm](https://glm.g-truc.net/0.9.9/index.html)
 * [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
 * [entt](https://github.com/skypjack/entt)
 * [yaml-cpp](https://github.com/jbeder/yaml-cpp)
 * [IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders)

***

<ins>**Screenshot:**</ins>

![Screenshot_1](Images/Screenshot_1.jpg)

***

<ins>**Note from the creator:**</ins>

This project serves as a means for me to learning core engine development, graphics programming,
mathematics and other stuff. This is formed by watching YouTube series on engine development 
as well as implementing my own little additions. This is NOT, by any means, an entire, 
from-scratch, all-by-myself, engine, as I am still learning what it takes to make a game 
engine in the hopes that one day I will be able to atleast create a minimum viable product
all by myself.

***

<ins>**For Udacity Nanodegree Capstone Project:**</ins>

List of all Rubric points covered in code:

 ### Loops, Functions, I/O
- The project demonstrates an understanding of C++ functions and control structures 
    - All Files  
- The project reads data from a file and process the data, or the program writes data to a file 
    - [WindowsPlatformUtils.cpp](Ghost/src/Platform/Windows/WindowsPlatformUtils.cpp) - Line no. 12, 35
    - [SceneSerializer.cpp](Ghost/src/Ghost/Scene/SceneSerializer.cpp) - Line 144, 172
- The project accepts user input and processes the input.
    - [EditorLayer.cpp](Ghost-Editor/src/EditorLayer.cpp) - Line no. 307 to 351
    - [WindowsInput.cpp](Ghost/src/Platform/Windows/WindowsInput.cpp) - Line no. 148 to 218

### Object Oriented Programming
- Templates generalize functions in the project.
    - [Base.h](Ghost/src/Ghost/Core/Base.h) - Line no. 27, 28, 
- Derived class functions override virtual base class functions.
    - [Window.h](Ghost/src/Ghost/Core/Window.h) - Line no. 32, 33
    - [WindowsWindow.h](Ghost/src/Platform/Windows/WindowsWindow.h) - Line no. 16, 17
- Classes follow an appropriate inheritance hierarchy.
    - [Window.h](Ghost/src/Ghost/Core/Window.h)
    - [WindowsWindow.h](Ghost/src/Platform/Windows/WindowsWindow.h)

### Memory Management
- The project makes use of references in function declarations.  
    - [Window.h](Ghost/src/Ghost/Core/Window.h) - Line 36, 43
- The project uses smart pointers instead of raw pointers.
    - [Base.h](Ghost/src/Ghost/Core/Base.h) - Line no. 28, 36, 30, 31, 35, 36, 38, 39

### Concurrency
- A mutex or lock is used in the project.
    - [Instrumentor.h](Ghost/src/Ghost/Debug/Instrumentor.h) - Line no. 40, 67, 86

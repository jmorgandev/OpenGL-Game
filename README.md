# OpenGL-Game
A short 3D game made with a specialized 2D game engine

Built to explore 3D game development with OpenGL, the engine is very specialized for this type of first person game. The engine loads in level data from the pixel data of a texture, meaning level editing is simple and efficient. It also parses XML files, but only for loading in a list of level file locations.

This engine uses OpenGL 2.1, meaning fixed function pipeline and immediate-mode drawing of triangles. This is by no means an optimized demo.

To prevent crashing, make sure the "data" and "res" folders are in the same directory as the 3D_OPENGL_ENGINE executable.

Technologies used:
- SDL2
- SDL2_image
- OpenGL 2.1
- freeglut
- tinyxml
- zlib

Last modification: August 2015
Last compiled: 21st September 2017

Compiled using Visual Studio 2017 (version 15.3.5)

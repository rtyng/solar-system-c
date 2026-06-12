This is my first attempt at learning OpenGL


OpenGL Milestones

1. Open a window
2. Draw a triangle
3. Draw a colored triangle
4. Draw a textured rectangle
5. Draw a rotating cube
6. Draw a sphere mesh
7. Apply Earth texture
8. Add lighting shader

From my research, OpenGL is heavily abstracted to the point where users have to do everything themselves
These milestones will take a lot of time, but no harm in trying it out then going back to raylib later


libraries

pacman -S mingw-w64-ucrt-x86_64-glfw
pacman -S mingw-w64-ucrt-x86_64-glew
pacman -S mingw-w64-ucrt-x86_64-stb

compile code

gcc file.c -o file.exe -lglfw3 -lglew32 -lopengl32 -lgdi32

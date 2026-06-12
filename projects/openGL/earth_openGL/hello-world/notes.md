A sphere is basically:

latitude lines
+
longitude lines
+
triangles

Modern pipeline:

vertex array
→ vertex buffer
→ shader program
→ draw call


gcc main.c -o practice.exe -lglew32 -lglfw3 -lopengl32 -lgdi32

How to think about Architecture for ahaders in OpenGL

Phase 1
-------
Initialize GLFW

Phase 2
-------
Create Window

Phase 3
-------
Initialize GLEW

Phase 4
-------
Compile Vertex Shader

Phase 5
-------
Compile Fragment Shader

Phase 6
-------
Link Shader Program

Phase 7
-------
Create Vertex Buffer

Phase 8
-------
Render Loop


Later on I'll be having two sets of 3 points in the vertices 



Stride = how far to jump to reach the next vertex
Offset = where this attribute begins inside each vertex
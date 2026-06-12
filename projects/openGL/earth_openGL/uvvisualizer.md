In OpenGL, everything seems to be built from vertices and indices.

The sphere that will represent the earth will have:

~10,000 vertices

+
~60,000 indices

=

sphere mesh

----------------------


Position + Color

just used these for the shader triangle, and the rectangle

Fragment shader recieved colors and interpolated them across the pixels

x y z r g b 

---------------------

Use these when I want geometry and a textured image

"this corner is red" -> "This corner corresponds this point on the image"

// position      // texture coordinate
0.5f, 0.5f, 0.0f,   1.0f, 1.0f

Top-right corner of rectangle

maps to

Top-right corner of image

x y z u v 

u = horizontal
v = vertical

Texture Image

(0,1) -------- (1,1)
  |              |
  |              |
  |              |
(0,0) -------- (1,0)



----------------------

These coordinates are just the above two ideas combined: Geometry, Colors, and Textures

x y z r g b u v

Eventually the sphere vertices will look like this:

x y z
nx ny nz -> these are normals and they are for the lighting
u v

----------------------

float vertices[] = {

    // positions        // UV

     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
};

(0,1) ----- (1,1)
  |           |
  | image     |
  |           |
(0,0) ----- (1,0)

Vertex Position (XYZ)
=
where the corner lives in space

Texture Coordinate (UV)
=
where that corner samples the image

------------------------------


1. UV Coordinates define Correspondence

"This point in geometry <-> This point in texture"

2. GPU interpolates UVs

uv = (0,0)

uv = (1,0)

For pixels between them, GPU automatically creates a bunch of values where interpolation occurs

3. Texture Lookup

fragment shader -> texture(myTexture, TexCoord)

TexCoord = (0.5,0.5)

GPU then looks at (0.5,0.5) and returns that color

----------------------------------

Thought Experiment

Top Left     -> (1,1)
Top Right    -> (0,1)
Bottom Left  -> (1,0)
Bottom Right -> (0,0)

Left side: u = 1
Right side: u = 0

Normally its the other way around: they're swapped
Image becomes mirrored horizontally

Geometry can be correct but this is why textures can sometimes appear backwards, inside out, or upside down on 3d models -> due to incorrect UV Mapping

This is what is currently happening in raylib for the 3d Earth Sphere:

geometry + UV coordinates + interpolation -> some sort of weird interaction which results in stretching at the poles after the 8k texture was applied to the image

----------------------------------

Vertex
    |
    v
UV
    |
    v
Fragment Shader
    |
    v
Texture Lookup
    |
    v
Image Pixel
    |
    v
Screen Color

Next Milestone:

Rectangle + Earth Texture Image

In Raylib, this was done in a couple lines of code. OpenGL requires a lot more work on the hidden steps:

1. Load image bytes from disk
2. Generate OpenGL texture ID
3. Bind texture
4. Configure wrapping/filtering
5. Upload image bytes to GPU
6. Tell shader about texture sampler
7. Pass UV coordinates
8. Sample texture in fragment shader




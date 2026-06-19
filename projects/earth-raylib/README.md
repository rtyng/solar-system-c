This project folder will be about using raylib to get used to making spheres

Current goal:

Using raylib to make the sphere look like earth

Sources:
https://en.wikipedia.org/wiki/Equirectangular_projection
https://commons.wikimedia.org/wiki/File:Solarsystemscope_texture_8k_earth_daymap.jpg
https://github.com/raysan5/raylib
https://learnopengl.com




build

gcc raylib_earth.c -o raylib_earth.exe $(pkg-config --cflags --libs raylib)


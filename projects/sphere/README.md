This project folder will be about using raylib to get used to making spheres

Current goal:

Using raylib to make the sphere look like earth

Sources:
https://en.wikipedia.org/wiki/Equirectangular_projection
https://commons.wikimedia.org/wiki/File:Solarsystemscope_texture_8k_earth_daymap.jpg

build

gcc spheres.c -o spheres.exe $(pkg-config --cflags --libs raylib)


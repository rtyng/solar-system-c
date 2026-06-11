# Solar System 2D Simulation

A basic 2D solar system visualization built in C using raylib.

## Current Features

- Sun and planet rendering
- Circular orbit paths
- Animated planetary motion
- Different orbit radii and orbital speeds

## Build

```bash
gcc main.c -o main.exe $(pkg-config --cflags --libs raylib)
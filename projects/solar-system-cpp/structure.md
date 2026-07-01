Things to consider

- I would have to implement lighting from the sun to 9 planets and pluto (sorry pluto) 
- 10 elliptical orbital paths
    - can add in moons and debris later
- 10 different rotations 
- putting all this together in 3d space

Ideas to pull from the 3d earth:

textured sphere
custom shader
rotation
starfield
camera control

File responsibilites

main.cpp
    - Owns the window, main loop, global camera, and calls everything.

planet.cpp/planet.hpp
    - Planet data and rendering: radius, rotation speed, texture, model, current position.

orbit.cpp / orbit.hpp 
    - Orbital math: circular orbit first, then elliptical/Keplerian orbit later.

lighting.cpp / lighting.hpp
    - Shader loading, light direction, uniform updates.

camera_controller.cpp / camera_controller.hpp
    - Orbit camera, zoom, click-to-focus, smooth movement.

ui.cpp / ui.hpp
    - Planet info panel, labels, debug text.

.cpp file  = implementation: how something works | where the logic lives
.hpp file  = interface: what other files are allowed to use

example:
orbit.hpp says:
    These functions/types exist.

orbit.cpp says:
    Here is how those functions actually work.


Math/Physics resources 

NASA/JPL for parameters
    - NASA has planet overview/fact-sheet material for physical and orbital properties, and JPL has approximate Keplerian elements for planet positions.
    - https://science.nasa.gov/solar-system/planets/


Main math topics

3D vectors
spherical coordinates
rotation matrices
Keplerian orbital elements
ellipses
inclination/orbital plane tilt
camera ray picking
dot product lighting







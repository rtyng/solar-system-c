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

main.c
    - Owns the window, main loop, global camera, and calls everything.

planet.c/planet.h
    - Planet data and rendering: radius, rotation speed, texture, model, current position.

orbit.c / orbit.h 
    - Orbital math: circular orbit first, then elliptical/Keplerian orbit later.

lighting.c / lighting.h
    - Shader loading, light direction, uniform updates.

camera_controller.c / camera_controller.h
    - Orbit camera, zoom, click-to-focus, smooth movement.

ui.c / ui.h
    - Planet info panel, labels, debug text.



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




Milestone Order

1. Sun + Earth only
2. Earth orbits Sun in 3D
3. Camera can zoom/focus on Earth
4. Add Mars
5. Generalize planet data into structs
6. Add all planets
7. Add elliptical orbits
8. Add inclination
9. Add click selection
10. Add UI/data panel
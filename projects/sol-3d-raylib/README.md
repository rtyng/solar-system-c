Considering this a solar system simulation I figure now is a good time to use raylib, my texture pipelines, and my intro physics knowledge to start building a 3d model of the solar system

Will be using raylib so I don't have to build everything from scratch


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


Dependencies so far:

<raylib.h>
<raymath.h>

---------------------------------------------------

Development loop:

orbit.h
      ↓
orbit.c
      ↓
main.c (minimal test)
      ↓
Verify it works
      ↓
Next module

will be easier to catch bugs and pinpoint where they are coming from
Considering this a solar system simulation I figure now is a good time to use the experience from learning raylib in C and my intro physics knowledge to start building a 3d model of the solar system

Sources:

JPL's Solar System Dynamics

- <https://ssd.jpl.nasa.gov>
“Solar System Dynamics. (Downloaded Year, Month, Date). (Title of the Page). <https://ssd.jpl.nasa.gov”>
- <https://ssd.jpl.nasa.gov/planets/approx_pos.html>
      - This source will be for integrating keplerian mechanics

UMD Numerical Integration with examples:

- I will refer to this source after I test out Euler's method and upgrade
- <https://physics.umd.edu/hep/drew/numerical_integration/>

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

module
      ↓
source
      ↓
main source
      ↓
Verify it works
      ↓
Next module

will be easier to catch bugs and pinpoint where they are coming from

----------------------------------------------------------

general build command for testing out orbit module implementation

g++ main.cpp orbit.cpp -std=c++20 -Wall -Wextra -Wpedantic -o solar_system.exe -lraylib -lopengl32 -lgdi32 -lwinmm

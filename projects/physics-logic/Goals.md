Goals of physics-logic is get the math and physics principles into code for an accurate eliptical orbit.
- I will be doing a lot of calculations and C code on paper before I put it all down into a c file. 
- Hopefully it will be good enough for an easy integration with the raylib earth and eventually the OpenGL Earth

-----------------------

Necessary variables, equations, etc.:

- Semi-major axis
- eccentricity
- oribtal period
- time 

- polar equation of an ellipse 
    - distance from the sun
    - semi-major axis
    - eccentricity
    - theta -> angle around the orbit, called the "True Anamoly"

translating polar to 3d 
- x = rcos(theta)
- z = rsin(theta)
- y = 0

- theta = 2pi*t/T


compile code

gcc earth-ellipse.c -o earth-ellipse.exe -lm
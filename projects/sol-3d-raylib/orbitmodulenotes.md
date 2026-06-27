orbit.h describes the orbit logic
    - what promises will orbit.h make?
        - that a planet's orbit can and will be updated
        - a planet's orbit will have a state that contains everything necessary to describe position and movement
        - a planat's orbit will have parameters that can be accessed

    - what files will use this information?
        - orbit.c will use these structs to implement the logic of the earth orbiting the sun
        - main.c will call these params in its init window to update the frames

    - what does an orbit have that needs to be described by main.c and orbit.c?
        - orbit needs to access and use params and state in for the logic
        - main needs to update the orbit in its window for rendering on the screen
            - what does main.c need orbit.c to do?
                - Initialize an orbit state from parameters.
                - Update the orbit state over time.
                - Return or expose the current position.
                - Reset the orbit.
            - these 4 things are all actions, not structs, so I need to declare these as functions that need specific information in order to update


In order to correctly update the state of an Orbit, UpdateOrbit() will need:
1. Where the orbit currently is -> OrbitParams params
2. What kind of orbit it is -> OrbitState state
3. How much time has passed this frame -> float dt 

How far along the circle should this planet move per unit time? -> Orbital Period

----------------------------------------------------------------

Crucial things to consider for the orbital mechanics

Raylib's 3d coordinate system
- satellites should start with tilted orbit spanning all 3 axis, due to raylib defaulting to a y-up coordinate system

Float precision drift 
- over long sim runs, single precision floating point numbers in raylib's Vector3 will introduce minor rounding errors. just need to keep dt small

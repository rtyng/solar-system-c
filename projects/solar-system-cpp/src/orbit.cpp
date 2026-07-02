/*
------------------------------------------------------------------------------
File: orbit.c

Purpose:
    - Implements orbital mechanics for planetary motion.
    - Promises not to create orbit objects, only to teach the compiler how an orbit behaves

Responsibilities:
    - Circular orbit calculations
    - Elliptical orbit calculations
    - Orbital inclination
    - Planet position updates

Current Task:
    - Orbital mechanics for the Sun's gravity on the Earth in 3d space

Used by:
    main.c
------------------------------------------------------------------------------
*/
#include "../include/orbit.hpp"


/* 
Compute the acceleration vector toward the Sun. 
------------------------------------------------------------------------

Responsibility of ComputeAcceleration():
    - Use an orbit object position vector and it's gravitational parameter to compute and return the acceleration vector toward the Sun
        - The acceleration vector is obtained by starting with Newton's Law of Universal Gravitation and substituting into his Second Law of Motion
    - The function is not responsible for considering time in it's calculations
    - The Sun will be centered at the origin point { 0, 0, 0 }

Input: 
    - An Orbit class object's GetPosition() and MU_SUN

Output: 
    - An acceleration vector 

*/
Vector3 ComputeAcceleration(Vector3 position, double mu)
{   
    // Need to compute the magnitude for finding the magnitude
    float mag_position = Vector3Length(position);

    // The position vector needs to be normalized in order to obtain the unit vector
    Vector3 norm_position = Vector3Normalize(position);

    // acceleration vector is then obtained through multiplying the magnitude x unit vector
    // magnitude is mu/r^2 -> use auto to convert to double
    auto mag = mu/(mag_position*mag_position);
    Vector3 acceleration = norm_position*mag;

    return acceleration;
}


// Advance the orbit one timestep using Euler integration.
void UpdateOrbit(Orbit *state, double mu, float dt)
{
    return;
}


// Convert meters into raylib world units.
Vector3 PhysicsToRender(Vector3 physicsPosition)
{
    return;
}
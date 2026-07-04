/*
------------------------------------------------------------------------------
File: orbit.c

Purpose and Promises:
    - Implements orbital mechanics for planetary motion.
    - Promises not to create orbit objects, only to teach the compiler how an orbit behaves
    - Promises not to worry about how these will be rendered

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


/*
Update the orbit within the simulation by time-step dt using Euler Integration 
Acceleration -> Velocity -> Position estimation
Notes:
    - Euler's method will work very well with the rendering loop due to continuous tiny approximations per frame 
    - Euler's method will also introduce error into the orbit so later this method will have to be replaced 

    - main.cpp owns the loop
    - Orbit::Update owns one timestep
    - ComputeAcceleration owns one acceleration calculation
-------------------------------------------------------------------------------
Responsibility:
    - Implement Euler's numerical integration method to advance the orbit by one simulation time step dt
Inputs:
    - double dt -> the time-step
Outputs:
    - void
*/
void Orbit::Update(double dt)
{
    // Assign ComputeAcceleration() to internal acceleration of object's data
    Vector3 acceleration = ComputeAcceleration();
    // Use Acceleration to update velocity | assign it to private member variable
    velocity = velocity + acceleration*dt;
    // Use Velocity to update position | assign to private member variable
    position = position + velocity*dt;
}


/*
Convert meters into raylib world units.
-----------------------------------------------
Responsibility:
    - This function will use the vari
Inputs:
    - double dt -> the time-step
Outputs:
    - void
*/ 
Vector3 PhysicsToRender(Vector3 physicsPosition)
{
    // 
    return;
}
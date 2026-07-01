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

Used by:
    main.c
------------------------------------------------------------------------------
*/
#include <math.h>
#include <raymath.h>

#include "../include/orbit.hpp"


// Computes gravitational acceleration acting on an orbit from the Sun.
Vector3 ComputeAcceleration(Vector3 position, double mu)
{   
    // center sun at origin 
    Vector3 sunPosition = { 0.0f, 0.0f, 0.0f };

    

   return;
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
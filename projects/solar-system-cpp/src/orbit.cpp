/*
------------------------------------------------------------------------------
File: orbit.c

Purpose:
    Implements orbital mechanics for planetary motion.

Responsibilities:
    - Circular orbit calculations
    - Elliptical orbit calculations
    - Orbital inclination
    - Planet position updates

Used by:
    main.c
------------------------------------------------------------------------------

Will need to create the logic for these:
    - Euler integration
    - Kepler equation solving
    - true anomaly calculation
    - elliptical position math
    - gravity acceleration math
*/
#include <math.h>
#include <raymath.h>

#include "../include/orbit.h"


// Computes gravitational acceleration toward the Sun.
Vector3 ComputeAcceleration(Vector3 position, double mu)
{

    float distance = Vector3Length(position);

    // Avoid division by zero.
    if (distance == 0.0f)
        return Vector3Zero();

    // Newton's law of gravitation:
    // a = -mu / r² * r̂

    float magnitude = -(float)(mu / (distance * distance));

    Vector3 direction = Vector3Normalize(position);

    return Vector3Scale(direction, magnitude);
}


// Advances the orbit one timestep using Euler integration.
void UpdateOrbit(OrbitState *state, double mu, float dt)
{
    // Compute acceleration from current position.
    Vector3 acceleration = ComputeAcceleration(state->position, mu);

    // Integrate velocity.
    state->velocity = Vector3Add(
        state->velocity,
        Vector3Scale(acceleration, dt)
    );

    // Integrate position.
    state->position = Vector3Add(
        state->position,
        Vector3Scale(state->velocity, dt)
    );
}


// Converts meters into raylib world units.
Vector3 PhysicsToRender(Vector3 physicsPosition)
{
    return Vector3Scale(physicsPosition, 1.0f / SIM_SCALE);
}
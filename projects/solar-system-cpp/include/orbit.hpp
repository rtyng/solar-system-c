/*
------------------------------------------------------------------------------
File: orbit.h

Public interface for orbital mechanics.

Provides functions for computing planetary positions and updating orbital
state.

Version 1:
circular orbit
position from angle

Dependencies
raylib.h 
raymath.h

main.c needs this module to use its functions
orbit.c needs this to prove implementations match the contract between main and the module
------------------------------------------------------------------------------
*/
#ifndef ORBIT_H
#define ORBIT_H

#include "raylib.h"

// Sun's gravitational parameter: GM_sun in m^3 / s^2
// mu -> Standard Gravitational Parameter of a celestial body
#define MU_SUN 1.32712440018e20

// Scale: 1 raylib unit = 1,000,000,000 meters
// Tweak this to zoom the solar system in/out
#define SIM_SCALE 1000000000.0

typedef struct {
    Vector3 position;     // Physics position in meters relative to the Sun
    Vector3 velocity;     // Physics velocity in meters per second
} OrbitState;

// Inputs are relative to the Sun | no pointers here. just returns a new Vector 3
Vector3 ComputeAcceleration(Vector3 position, double mu);

// Returns nothing. *state -> gives location of original orbit in memory | Can use UpdateOrbit(&state) to change position and velocity 
void UpdateOrbit(OrbitState *state, double mu, float dt);

// Coordinate conversion helper | Returns Vector3 object
Vector3 PhysicsToRender(Vector3 physicsPosition);

#endif


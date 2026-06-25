/*
------------------------------------------------------------------------------
File: orbit.h

Public interface for orbital mechanics.

Provides functions for computing planetary positions and updating orbital
state.

Version 1:
circular orbit
position from angle

OrbitParams describes the circle.
OrbitState stores the current point on that circle.
UpdateOrbit moves that point forward.

Notes on interface implementations


Will be using raylib.h for its structs
------------------------------------------------------------------------------
*/
#include <raylib.h>

// contains semiMajorAxis, eccentricity, OrbitalPeriod, inclination, initialPhase. All floats
typedef struct {

    float semiMajorAxis;
    float eccentricity;
    float OrbitalPeriod;
    float inclination;
    float initialPhase;

} OrbitParams;

// contains position, velocity, acceleration, currentAngle, and elapsedTime. 
typedef struct {

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    float currentAngle;
    float elapsedTime;

} OrbitState;

// Initializes and returns the starting state of an orbit from the given orbital parameters.
OrbitState InitOrbit( OrbitParams params ){

    OrbitState state;

    state.elapsedTime = 0.0f;
    state.currentAngle = params.initialPhase;
    
    // version 1 circular orbit comes from position
    state.position.x = params.semiMajorAxis*cosf(state.currentAngle);
    state.position.y = 0.0f;
    state.position.z = params.semiMajorAxis*sinf(state.currentAngle);

    // start with zero acceleration and velocity for now
    state.velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    state.acceleration = (Vector3){ 0.0f, 0.0f, 0.0f };


    return state;
}


// UpdateOrbit() takes an input OrbitState state and updates its values
OrbitState UpdateOrbit( OrbitState state ){

    OrbitState updatedState;

    updatedState.elapsedTime = updatedState.elapsedTime - state.elapsedTime;
    // take a break


    return updatedState;
}

// returning

int ReturnOrbit(){





    return 0;
}

// resetting

int ResetOrbit(){






    return 0; 
}





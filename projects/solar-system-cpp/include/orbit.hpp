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

main.c needs this module to use its functions
orbit.c needs this to prove implementations match the contract between main and the module
------------------------------------------------------------------------------
*/
#ifndef ORBIT_HPP
#define ORBIT_HPP

#include <raylib.h>

// Sun's gravitational parameter: GM_sun in m^3 / s^2
constexpr double MU_SUN = 1.32712440018e20;

// Scale: 1 raylib world unit = 1,000,000,000 meters
constexpr double SIM_SCALE = 1.0e9;

class Orbit
{
public:
    Orbit(Vector3 initialPosition, Vector3 initialVelocity, double mu = MU_SUN);

    void Update(float dt);

    Vector3 GetPosition() const;
    Vector3 GetVelocity() const;
    Vector3 GetRenderPosition() const;

    void SetPosition(Vector3 newPosition);
    void SetVelocity(Vector3 newVelocity);

private:
    Vector3 position;
    Vector3 velocity;
    double gravitationalParameter;

    Vector3 ComputeAcceleration() const;
};

#endif
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

main.c only needs to worry that an orbit class object can update itself
orbit.c needs this to prove implementations match the contract between main and the module
------------------------------------------------------------------------------
*/
#ifndef ORBIT_HPP
#define ORBIT_HPP

#include <raylib.h>
#include <raymath.h>


// Sun's gravitational parameter: GM_sun in m^3/s^2
constexpr double MU_SUN = 1.32712440018e20;

// Scale: 1 raylib world unit = 1,000,000,000 meters
constexpr double SIM_SCALE = 1.0e9;

class Orbit
{
public:
    /* 
    Orbit class constructor for creating and initializing a new orbit object
        inputs:
            - Vector3 initialPosition
            - Vector3 initialVelocity
            - double mu = MU_SUN | defaults to the Sun's gravitational parameter in m^3/s^2
                - gravitational parameter
    */
    Orbit(Vector3 initialPosition, Vector3 initialVelocity, double mu = MU_SUN);

    /* 
    void Update() -> Modifier
    It will advance an orbit object forward by one simulated time-step dt with
    user's choice of numerical integration method
    */
    void Update(float dt);

    /*
    The following getters grab position, velocity, and render position information from private access
    read-only member functions
    */
    Vector3 GetPosition() const;
    Vector3 GetVelocity() const;
    Vector3 GetRenderPosition() const;

    // Setter functions used to replace position and velocity with new vector3s
    // Modifier functions
    void SetPosition(Vector3 newPosition);
    void SetVelocity(Vector3 newVelocity);

private:
    // private member variables
    Vector3 position;
    Vector3 velocity;
    double gravitationalParameter;

    // ComputeAcceleration() promises not to modify the orbit object in question
    // read-only member function
    Vector3 ComputeAcceleration() const;
};

#endif
/*
 * Earth Ellipse
 * This program calculates the properties of an ellipse representing the Earth's orbit.
*/
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

// typedef struct allows me to create a vector that can be used for 3D calculations
typedef struct {
   double x, y, z;

} Vect3;


// Semi-major axis, eccentricity, and orbital period
typedef struct {
   double a, e, T;

} EarthOrbit;

// Calculate the position of the Earth in its orbit at a given time.
Vect3 calculateEarthPosition(EarthOrbit orbit, double time_days) {
   // Implementation for calculating Earth's position
   Vect3 position;

   // declare theta aka the true anomaly
   double theta = (2 * PI * time_days) / orbit.T;
   printf("True Anomaly: %f\n", theta);
   printf("Time (days): %f\n", time_days);
   printf("Orbital Period: %f\n", orbit.T);

   double a = orbit.a; // semi-major axis
   double e = orbit.e; // eccentricity
   printf("Semi-major axis: %f\n", a);
   printf("Eccentricity: %f\n", e);


   double r = a * (1 - e * e) / (1 + e * cos(theta)); 
   printf("Distance from the Sun: %f\n", r);
   printf("Semi-major axis: %f\n", a);
   //y should be zero I think in this case
   position.x = r * cos(theta);
   position.z = r * sin(theta);
   position.y = 0.0;
   printf("Position: (%f, %f, %f)\n", position.x, position.y, position.z);

   return position;
}

// test it out at t = 0, 91, 182, 273 days
int main() {
   EarthOrbit earthOrbit;
   earthOrbit.a = 1.0; // in AU
   earthOrbit.e = 0.0167; // eccentricity
   earthOrbit.T = 365.25; // in days

   Vect3 position = calculateEarthPosition(earthOrbit, 0.0);
   Vect3 position2 = calculateEarthPosition(earthOrbit, 91.0);
   Vect3 position3 = calculateEarthPosition(earthOrbit, 182.0);
   Vect3 position4 = calculateEarthPosition(earthOrbit, 273.0);

   printf("Position at 0 days: (%f, %f, %f)\n", position.x, position.y, position.z);
   printf("Position at 91 days: (%f, %f, %f)\n", position2.x, position2.y, position2.z);
   printf("Position at 182 days: (%f, %f, %f)\n", position3.x, position3.y, position3.z);
   printf("Position at 273 days: (%f, %f, %f)\n", position4.x, position4.y, position4.z);

   return 0;
}




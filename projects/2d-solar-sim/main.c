/* Randy's 2D Solar System Simulation 

Final Goal:
    - The orbital paths of the planets should be accurately represented in 2D space.
        - Accurately means implementing where the planets are at today, and how those orbits will 
        - evolve over the rest of the year according to their actual orbital mechanics.

Caveats:
    - The simulation is 2D, so it will not show the true 3D nature of the solar system.
    - The orbits are simplified and do not account for the gravitational influences of other celestial bodies.
    - The relative sizes of the planets are not to scale.


References:
    - https://en.wikipedia.org/wiki/Solar_System
https://ssd.jpl.nasa.gov/

*/


#include <raylib.h>
#include <math.h>

int main(void){

    // Initialize the simulated days: : 1 real second = 10 simulated days
    int simulatedDays = (int)(GetTime() * 10);


    // Window needs to be a lot larger, will just make it to my screen size
    InitWindow(2560, 1600, "Our Solar System");

    

    while (!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Date: 2026-06-11", 40, 40, 30, WHITE);
        DrawText("Randy's 2D Solar System Simulation", 40, 80, 30, WHITE);

        // Display the number of simulated days
        DrawText(TextFormat("Simulated Days: %d", simulatedDays), 40, 120, 30, WHITE)
        
        
        ;
        //declare coordinates and angle

        float t = GetTime();
        float sunX = 1280;
        float sunY = 800;
        float mercury1X = 1280 + 150 * cos(t);
        float mercury1Y = 800 + 150 * sin(t);
        float venus2X = 1280 + 150 * cos(t);
        float venus2Y = 800 + 150 * sin(t);

        //DrawCircleLines should come before DrawCircle to preserve while loop data flow
        DrawCircleLines(sunX, sunY, 150, GRAY);
        DrawCircleLines(sunX, sunY, 220, GRAY);
        DrawCircleLines(sunX, sunY, 290, GRAY);
        DrawCircleLines(sunX, sunY, 360, GRAY);
        DrawCircleLines(sunX, sunY, 430, GRAY);
        DrawCircleLines(sunX, sunY, 500, GRAY);
        DrawCircleLines(sunX, sunY, 570, GRAY);
        DrawCircleLines(sunX, sunY, 640, GRAY);
        DrawCircleLines(sunX, sunY, 710, GRAY);


        
        // Orbits aren't perfect but close enough for now

        DrawCircle(sunX, sunY, 50, YELLOW);

        DrawCircle(sunX + 150 * cos(t), sunY + 150 * sin(t), 20, ORANGE);
        DrawCircle(sunX + 220 * cos(t*0.7), sunY + 220 * sin(t*0.7), 15, BLUE);
        DrawCircle(sunX + 290 * cos(t*0.5), sunY + 290 * sin(t*0.5), 10, GREEN);
        DrawCircle(sunX + 360 * cos(t*0.3), sunY + 360 * sin(t*0.3), 5, RED);
        DrawCircle(sunX + 430 * cos(t*0.2), sunY + 430 * sin(t*0.2), 5, BEIGE);
        DrawCircle(sunX + 500 * cos(t*0.1), sunY + 500 * sin(t*0.1), 5, GOLD);
        DrawCircle(sunX + 570 * cos(t*0.05), sunY + 570 * sin(t*0.05), 5, GRAY);
        DrawCircle(sunX + 640 * cos(t*0.02), sunY + 640 * sin(t*0.02), 5, BROWN);
        DrawCircle(sunX + 710 * cos(t*0.01), sunY + 710 * sin(t*0.01), 5, DARKBROWN);



        EndDrawing();
    }

    CloseWindow();  

    return 0;
}

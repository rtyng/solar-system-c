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
#include <time.h>



int main(void){

    //Need to set up the correct times for correct dates and to stop at this day next year

    struct tm startDate = {0};
    startDate.tm_year = 2026 - 1900; // Year since 1900
    startDate.tm_mon = 5; // June (0-indexed)
    startDate.tm_mday = 11; // Day of the month
    time_t start = mktime(&startDate);

    struct tm endDate = {0};
    endDate.tm_year = 2027 - 1900; // Year since 1900
    endDate.tm_mon = 5; // June (0-indexed)
    endDate.tm_mday = 11; // Day of the month
    time_t end = mktime(&endDate);

    int maxSimulatedDays = 365;
    int simulatedDays = 0;


    // Window needs to be a lot larger, will just make it to my screen size
    InitWindow(2560, 1600, "Our Solar System");

    
    // this loop runs about 60 frames per second
    while (!WindowShouldClose()){

        // declare time and simulation speed
        float t = GetTime();
        float simulationspeed = 5.0f;


        // convert real time to simulated days
        simulatedDays = (int)(t*simulationspeed);


        // stop at 365 days
        if (simulatedDays >= maxSimulatedDays) 
        {
            simulatedDays = maxSimulatedDays;
            break;
        }


        // convert simulated days to real dates
        time_t currentTime = start + (simulatedDays * 24 * 60 * 60);
        struct tm *current = localtime(&currentTime);



        //Begin drawing
        BeginDrawing();
        ClearBackground(BLACK);


        // Display the current date and Title
        DrawText(TextFormat("Date: 6/11/2026", 
            current->tm_year + 1900, 
            current->tm_mon + 1, current->tm_mday), 
            40, 40, 30, WHITE);
        DrawText("Randy's 2D Solar System Simulation", 40, 80, 30, WHITE);

        // Display the number of simulated days
        DrawText(TextFormat("Simulated Days: %d", simulatedDays), 40, 120, 30, WHITE);
        
        // Display the future date | the starting date is off by 10 days
        DrawText(
            TextFormat(
                "Future Date: %04d-%02d-%02d", 
                current->tm_year + 1900,
                current->tm_mon + 1,
                current->tm_mday
            ), 
                40, 160, 30, WHITE);
        
        



        // positions and orbits 
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

#include <raylib.h>
#include <math.h>

int main(void){
    
    InitWindow(1400, 700, "Look at these shapes");
    //shapes off center, just need to use half of width and height below



    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        
        float t = GetTime();

        // The second DrawCircle was supposed to be it's own planet and not a moon
        // Probably just need a slight adjustment
        DrawCircle(700, 350, 50, YELLOW);
        DrawCircle(400 + 150 * cos(t), 225 + 150 * sin(t), 20, BLUE);
        DrawCircle(350 + 150 * cos(t), 350 + 150 * sin(t), 15, GREEN);
        EndDrawing();
    }

    CloseWindow();  

    return 0;
}

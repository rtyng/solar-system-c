#include <raylib.h>

int main(void){
    DrawCircle(400, 225, 50, RED);
    DrawRectangle(100, 100, 200, 200, BLUE);
    DrawLine(0, 0, 800, 450, GREEN);

    InitWindow(800, 450, "Look at these shapes");

    

    return 0;
}
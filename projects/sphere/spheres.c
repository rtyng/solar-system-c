/* Randy's 3D Sphere Simulation 

Goals:

Good camera control
Add detail to the sphere to make it look like earth

*/
#include <raylib.h>
#include <math.h>



int main(void)
{   

    // initialize the window
    InitWindow(1440, 800, "3D Sphere Lab");


    // initialize the 3D camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;


    float cameraDistance = 6.0f;
    float yaw = 0.8f;    // left/right angle
    float pitch = 0.5f;  // up/down angle



    // set the target frame rate, increase to 240 for fun
    SetTargetFPS(240);

    while (!WindowShouldClose())
    {   

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // Get the mouse movement
            Vector2 mouseDelta = GetMouseDelta();

            yaw += mouseDelta.x * 0.01f;
            pitch -= mouseDelta.y * 0.01f;
        }


        // add stops so camera doesn't go haywire
        if (pitch > 1.57f) pitch = 1.57f;
        if (pitch < -1.57f) pitch = -1.57f;

        /*
        this code didn't work as expected
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            cameraDistance -= GetMouseWheelMove() * 0.5f;
        }
        */
        

        // trying different approach
        cameraDistance -= GetMouseWheelMove() * 0.5f;


        // convert spherical coordinates to Cartesian coordinates
        camera.position.x = cameraDistance * cosf(pitch) * cosf(yaw);
        camera.position.y = cameraDistance * sinf(pitch);
        camera.position.z = cameraDistance * cosf(pitch) * sinf(yaw);


        // updates at 240 frames per second | above is where I can add mouse interaction
        // camera movement depends on input in every frame
        // this is unnecessary with the above approach
        //UpdateCamera(&camera, CAMERA_FREE);
        

        // draw the scene
        BeginDrawing();
        ClearBackground(BLACK);

        // begin 3D mode
        BeginMode3D(camera);


        // draw the 3D objects and grid
        DrawSphere((Vector3){ 0, 0, 0 }, 1.5f, BLUE);
        DrawSphereWires((Vector3){ 0, 0, 0 }, 1.5f, 32, 32, WHITE);
        DrawGrid(10, 1.0f);


        // end 3D mode
        EndMode3D();


        // draw 2D elements
        DrawText("3D Sphere Lab", 40, 40, 30, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

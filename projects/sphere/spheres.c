/* Randy's 3D Sphere Simulation 

Goals:

Good camera control
Add detail to the sphere to make it look like earth

Milestones
    1. Wireframe earth
    2. Textured earth  
        1. Wireframe sphere
        2. Textured Earth: oceans + continents
        3. Rotation
        4. Lighting
        5. Clouds / atmosphere
    3. earth rotation
    4. directional sunlight 
    5. moon

Current Progress
    - The earth is currently textured with a high-resolution image.
        - There is a lot of stretching from the poles, texture and mesh UVs are in disagreement with each other
        - texture is loading fine at 1920x960, so the issue is likely in the mesh generation or UV mapping.

*/
#include <raylib.h>
#include <math.h>

#define STAR_COUNT 1000


int main(void)
{   


    // initialize the window
    InitWindow(2560, 1600, "3D Sphere Lab");


    // generate a set of random stars
    Vector2 stars[STAR_COUNT];
    Color starColors[STAR_COUNT];

    for (int i = 0; i < STAR_COUNT; i++){
        stars[i].x = GetRandomValue(0, 2560);
        stars[i].y = GetRandomValue(0, 1600);

        int brightness = GetRandomValue(100, 255);
        starColors[i] = (Color){ brightness, brightness, brightness, 255 };
    }

    // set up earth's rotation
    float earthRotation = 0.0f;
    float earthRotationSpeed = 10.00f;

    // set up the earth's axial tilt
    float earthAxialTilt = 23.44f * DEG2RAD;
    Vector3 earthAxis = (Vector3){ 0.0f, cosf(earthAxialTilt), sinf(earthAxialTilt) };


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



    // load assets 
    Texture2D earthTexture = LoadTexture("assets/earth_texture_8k.png");

    // print dimensions of the loaded texture
    TraceLog(LOG_INFO, "Earth texture dimensions: %i x %i", earthTexture.width, earthTexture.height);

    // verify that the texture was loaded correctly
    if (earthTexture.id == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load earth texture");
        return -1;
    }
    TraceLog(LOG_INFO, "Earth texture loaded successfully");


    // setting up mesh, model, texture | use 256 for smoothness
    // 128 rings shows its a mapping issue
    Mesh earthMesh = GenMeshSphere(1.5f, 128, 256);
    Model earth = LoadModelFromMesh(earthMesh);

    earth.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = earthTexture;
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


        // set the rotation of the earth

        earthRotation += earthRotationSpeed*GetFrameTime();
        // draw the scene
        BeginDrawing();
        ClearBackground(BLACK);

        // draw the stars
        for (int i = 0; i < STAR_COUNT; i++){
            DrawPixelV(stars[i], starColors[i]);
        }

        // begin 3D mode
        BeginMode3D(camera);


        // use DrawModelEx to draw and update the earth with rotation
        // to get accurate with earth's rotation axis, will need to adjust the rotation vector's z value and use trig above to get an accurate vector
        DrawModelEx(earth, 
            (Vector3){ 0, 0, 0 },
            earthAxis,
            earthRotation,
            (Vector3){ 1.0f, 1.0f, 1.0f }, 
            WHITE);
        // DrawSphereWires((Vector3){ 0, 0, 0 }, 1.5f, 32, 32, WHITE);
        DrawGrid(10, 1.0f);


        // end 3D mode
        EndMode3D();


        // draw 2D elements
        DrawText("Planet Earth in C by Randy Tyng", 40, 40, 30, WHITE);

        EndDrawing();
    }

    UnloadModel(earth);
    UnloadTexture(earthTexture);

    CloseWindow();
    return 0;
}

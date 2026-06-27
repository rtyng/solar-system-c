/* 
Randy's 3D Realistic Earth Simulation 
*/
#include <raylib.h>
#include <math.h>
#include <raymath.h>
#include <stdio.h>
#define STAR_COUNT 1000


int main(void)
{   

    // initialize the window for my screen
    InitWindow(1920, 1080, "3D Sphere Lab");


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


    // generate a set of random stars
    Vector2 stars[STAR_COUNT];
    Color starColors[STAR_COUNT];

    for (int i = 0; i < STAR_COUNT; i++){
        stars[i].x = GetRandomValue(0, 2560);
        stars[i].y = GetRandomValue(0, 1600);

        int brightness = GetRandomValue(100, 255);
        starColors[i] = (Color){ brightness, brightness, brightness, 255 };
    }

    
    /*
    Define sun position and the light direction

    lightDirection was normalized by co-pilot because graphics programmers use this as a stopgap against future changes.

    Normalizing (-1.0,0.0,0.0) returns (1.0,0.0,0.0). 
    
    Without normalization the dot product would return angle x vector length instead of just the angle
    */
    Vector3 sunPosition = (Vector3){ 5.0f, 0.0f, 0.0f };
    Vector3 lightDirection = Vector3Normalize((Vector3){ -1.0f, 0.0f, 0.0f });
    

    // set up earth's rotation and axial tilt
    float earthRotation = 0.0f;
    float earthRotationSpeed = 10.00f;
    float earthAxialTilt = 23.44f * DEG2RAD;
    Vector3 earthAxis = (Vector3){ 0.0f, cosf(earthAxialTilt), sinf(earthAxialTilt) };


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
    // GenMeshSphere generates a Mesh struct that includes surface normals that automatically point straight outward from the center
    Mesh earthMesh = GenMeshSphere(1.5f, 128, 256);
    Model earth = LoadModelFromMesh(earthMesh);

    earth.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = earthTexture;

    // cheking for shader loading errors
    printf("Loading shaders...\n");

    // create the lightshader using .vs and .fs files
    Shader lightShader = LoadShader(
    "resources/earth_lighting.vs",
    "resources/earth_lighting.fs"
    );

    printf("Shader ID: %d\n", lightShader.id);

    // set the shader uniform value for sunPosition and lightDirection
    SetShaderValue(lightShader, GetShaderLocation(lightShader, "sunPosition"), &sunPosition, SHADER_UNIFORM_VEC3);
    SetShaderValue(lightShader, GetShaderLocation(lightShader, "lightDirection"), &lightDirection, SHADER_UNIFORM_VEC3);

    // get shader uniform locations
    int sunPositionLoc = GetShaderLocation(lightShader, "sunPosition");
    int lightDirectionLoc = GetShaderLocation(lightShader, "lightDirection");

    // assign the shader to the earth's material
    earth.materials[0].shader = lightShader;

    // set the target frame rate to 240 for fun
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
        
        
        // trying different approach
        cameraDistance -= GetMouseWheelMove() * 0.5f;


        // convert spherical coordinates to Cartesian coordinates
        camera.position.x = cameraDistance * cosf(pitch) * cosf(yaw);
        camera.position.y = cameraDistance * sinf(pitch);
        camera.position.z = cameraDistance * cosf(pitch) * sinf(yaw);

        // set the rotation of the earth
        earthRotation += earthRotationSpeed*GetFrameTime();


        // draw the scene, black background for representing the stars
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

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



camera = persistent object
mouse/keyboard input = checked every frame
camera position/target = updated every frame
scene = redrawn every frame

Remember: every single frame these below are happening

Input
Update
Draw


Declarations/initial setup outside loop
Interactive behavior inside loop

Currently working with UpdateCamera(&camera, CAMERA_FREE); 
    - raylib probably has a mouse interaction option


Flow behind a user clicking and dragging their perspective around that point

Mouse drag changes angles
Mouse wheel changes distance
Angles + distance calculate camera.position
Camera always looks at camera.target




This code below is the core of this small program in terms of camera and perspective movement

    // convert spherical coordinates to Cartesian coordinates
    camera.position.x = cameraDistance * cosf(pitch) * cosf(yaw);
    camera.position.y = cameraDistance * sinf(pitch);
    camera.position.z = cameraDistance * cosf(pitch) * sinf(yaw);

yaw   = rotate around the object left/right
pitch = rotate above/below the object
distance = how far the camera is from the object



Pipeline for making the sphere look like earth

plain sphere
    ↓
textured sphere
    ↓
rotating textured sphere
    ↓
lighting
    ↓
cloud layer / atmosphere effect
    ↓
shader later


Lighting question

can i make the brightness depend on which way the surface is facing relative to the Sun?

Conceptual roadmap for shaders:
- I pretty much did this already with openGL but its been a couple days and I need a reminder

Setup phase, before loop:
1. Load Earth texture
2. Generate sphere mesh/model
3. Assign texture to model material
4. Load shader
5. Assign shader to model material
6. Get shader uniform locations
7. Define sun/light direction

Before I even run the loop: 

I need to go into those .fs and .vs files and put stuff in there for raylib to use. I am now the one who needs to tell the GPU what to do

Earth Mesh
    ↓
Vertices
    ↓
Vertex Shader

.vs -> vertex shader file
.fs -> fragment shader file

the earth sphere has thousands of vertices where each vertex gets processed by the vertex shader

the fragment shader runs once for every pixel

conceptually for the .vs:

Take mesh data
Pass texture coordinates along
Pass normals along
Put vertices on screen

conceptually for the .fs:

Get Earth texture color
Measure angle between surface and Sun
Darken night side
Keep day side bright

in line 15 brightness is just the max of the dot product because there is no such thing as negative light

float brightness =
        max(dot(normalize(fragNormal),
                normalize(lightDirection)), 0.0);

turns out this the core of what is going on for brightness under the hood in anything that needs to use graphics

dot product uses cosine, so in terms of the earth relative to the sun's light, the angle is pretty representative, so at noon standing on earth with the sun directly overhead, this dot product specifically comes out to 1 = maximum brightness


gonna have to mess with numbers a little bit after I get this all runnning

light


    ↓
Triangles
    ↓
Rasterization
    ↓
Pixels
    ↓
Fragment Shader
    ↓
Screen

Loop phase:
1. Update camera/input
2. Update Earth rotation
3. Update shader values if they change
4. BeginDrawing()
5. BeginMode3D(camera)
6. DrawModelEx(...)
7. EndMode3D()
8. EndDrawing()



Current Goal as of 9:32 am 6/19/2026

- make the lighting realistic
    - current issues
        - the dark side is transparent | can see the stars in the background
        - the dark side is static and rotates the earth
    - thoughts on current issues 
        - Need to adjust the .fs file
            - the fragment shader is where the lighting becomes something
            - max(dot(normal of fragNormal and lightDirection))
            - I dont think changing the vector of the sun's light direction is going to do much
                - Will focus on adjusting the dot product and fragnormal
                - Will need to find documentation for openGL 3.30 core and raylib to figure out what I can do
                - Will also need to understand more of what fragNormal is
    

    - Research Goals
        - check out raylib examples
            - https://github.com/raysan5/raylib/blob/master/examples/shaders/resources/shaders/glsl330/lighting.fs
                - check out the code for the examples and see if I can't figure something out
                - one of the first examples utilized rlgl
        - LearnopenGL
            - https://learnopengl.com/PBR/Lighting


New Session at 2:21 pm 6/19/26

The issue with the dark side rotating with the earth was resolved in the vertex shader (.vs) file. I needed to use raylib's matModel, a 4 x 4 matrix model that needed to be inverted, transposed, turned into 3 x 3 matrix, multiplied by the vertexNormal and then normalized in order to get the get fragNormal out of "object space" and into the local space of my screen. The dark side of the earth was there before but it was moving with the earth's rotation

Next goal with the lighting:
    - The dark side is transparent and it isn't one line. It's not just the dark side either. It seems like the fragment and vertex shading has made the entire Earth sphere somewhat transparent depending on how I move it around and view it at different angles. 
    - I think the issue lies in the shading. Looking back at older videos, the sphere model was not see through at all. 
        - I am going to need to more reading and research into LearnOpenGL and into raylib as well.

Session at 6/21/26 at 11:50 am

- goal for this session
    - the dark side is completely see through
        - the opposite side of the globe is not
    - why is that?
        - Has to be some issue with shaders and the math in the .vs and .fs files
        - the earth was not see through at all before I tried to implement lighting
    - Potential path to solution
        - look at the raylib github 
            - look into the .vs and .fs files for their examples
                - figure out what their shader code is doing 
    - Raylib basic lighting example by Chris Camacho 
        - in this example the shader was updated with the camera view vector in the while loop
        - he also had to use BeginShaderMode under BeginDrawing in order to make that happen
            - try it out
            - chris didn't have as much camera code for that example to work the way it did so I am just going to do what he did to cut down what's inside the while loop

        - going to try and compile it without using BeginShaderMode under BeginDrawing and see what happens
        - copying an example was a bad idea. it compiled but the camera positioning code I have is what I need for my purposes

- Concept of .vs and .fs 
    - Vertex Shaders -> Geometry 
        - the vertex shaders are preparing the data for the fragment shader
    - Fragment Shaders -> Surface/Pixel 
        - What color should this pixel be?
            - This is where I should focus on for this issue 
    - Investigative questions
        - What color is being sent out?
        - what alpha value is being sent out?
        - what brightness value is being sent out?
camera = persistent object
mouse/keyboard input = checked every frame
camera position/target = updated every frame
scene = redrawn every frame


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

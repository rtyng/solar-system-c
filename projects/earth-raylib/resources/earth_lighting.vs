#version 330

// vertex attributes, shouldn't need color for earth with a texture wrapped around it
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

// output for fragment shader
out vec2 fragTexCoord;
out vec3 fragNormal;

// 4 x 4 Model-View-Projection | Translates 3d earth from object space to my screen
uniform mat4 mvp;

// Need to use raylib's 4 x 4 Model Matrix, then use it to adjust fragNormal
uniform mat4 matModel;

void main()
{
    // sending vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;

    /*
    Need to adjust fragNormal
    matModel represents where the object exists in world space 
    the normal transform will manipulate that tell the gpu where the surface faces in worldspace

    inverting, transposing, and changing matModel to 3 x 3 -> 3 x 3 matModel * 3 x 3 vertexNormal -> normalize it
    */
    fragNormal = normalize(mat3(transpose(inverse(matModel))) * vertexNormal);

    // Calculating final vertex position
    // This transforms each vertex from model space | tells gpu where to draw vertexs
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}

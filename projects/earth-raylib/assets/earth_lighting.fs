#version 330

// Input vertex attributes from vertex shader
in vec2 fragTexCoord;
in vec3 fragNormal;

// Uniform values
uniform sampler2D texture0;
uniform vec3 lightDirection;

// Output fragment color
out vec4 finalColor;

void main()
{
    
    vec4 texColor = texture(texture0, fragTexCoord);

    float brightness =
        max(dot(normalize(fragNormal),
                normalize(lightDirection)), 0.0);

    finalColor = texColor * brightness;
}
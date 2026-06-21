#version 330

// Input vertex attributes from vertex shader
in vec3 fragPosition;
in vec2 fragTexCoord;
in vec3 fragNormal;

// Uniform values
uniform sampler2D texture0;
uniform vec3 lightDirection;

// Output fragment color
out vec4 finalColor;

void main()
{
    // texColor is a 4d vector -> (R, G, B, A)
    vec4 texColor = texture(texture0, fragTexCoord);

    // determing how much sunlight hits the pixels
    float brightness =
        max(dot(normalize(fragNormal),
                normalize(lightDirection)), 0.0);



    // took two hours to figure that out -> certified graphics programmer
    finalColor.a = texColor.a;
    finalColor.rgb = texColor.rgb * brightness;
}
#version 330

in vec2 fragTexCoord;
in vec3 fragNormal;

uniform sampler2D texture0;
uniform vec3 lightDirection;

out vec4 finalColor;

void main()
{
    vec4 texColor = texture(texture0, fragTexCoord);

    float brightness =
        max(dot(normalize(fragNormal),
                normalize(lightDirection)), 0.0);

    finalColor = texColor * brightness;
}
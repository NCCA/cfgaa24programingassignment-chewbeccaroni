#version 410 core

layout(location=0) out vec4 fragColour;
layout(location=1) out vec4 brightColour;
in vec3 particleColour;
in vec3 lightColour;

uniform sampler2D tex;

void main()
{
    float ambientStrength = 0.1;
    float objectColour = (0.0,0.5,0.5,1);
    vec3 ambient = ambientStrength * lightColour;

    vec3 result = ambient * objectColour;
    fragColour = vec4(result, 1.0);

    float brightness = dot(fragColour.rgb, vec3(0.2,0.7,0.07));
    if(brightness > 1.0)
        brightColour = vec4(fragColour.rgb, 1.0);
    else
        brightColour = vec4(0.0, 0.0, 0.0, 1.0);
}
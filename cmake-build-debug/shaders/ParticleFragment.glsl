//#version 410 core
//
//layout(location=0) out vec4 fragColour;
//layout(location=1) out vec4 brightColour;
//in vec3 particleColour;
//in vec3 lightColour;
//
//uniform sampler2D tex;
//
//void main()
//{
//    float ambientStrength = 0.1;
//    float objectColour = (0.0,0.5,0.5,1);
//    vec3 ambient = ambientStrength * lightColour;
//
//    vec3 result = ambient * objectColour;
//    fragColour = vec4(result, 1.0);
//
//    float brightness = dot(fragColour.rgb, vec3(0.2,0.7,0.07));
//    if(brightness > 1.0)
//        brightColour = vec4(fragColour.rgb, 1.0);
//    else
//        brightColour = vec4(0.0, 0.0, 0.0, 1.0);
//}
#version 410 core

layout(location=0) out vec4 fragColour;
in vec4 particleColour;
in vec3 fs_Normal;
uniform float offset[5] = float[](0.0, 1.0, 2.0, 3.0, 4.0);
uniform float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);
out vec4 out_Normal;
out vec4 out_Colour;

void main()
{
    fragColour=particleColour * weight[0];
    for (int i=1; i<5; i++)
    {
        fragColour += particleColour * weight[i];
    }
}


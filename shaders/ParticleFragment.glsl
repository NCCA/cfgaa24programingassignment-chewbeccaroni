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
//#version 410 core
//
//layout(location=0) out vec4 fragColour;
//in vec2 particleColour;
//in vec2 TexCoords;
//uniform sampler2D screenTexture;
//
//
//void main()
//{
////      fragColour= particleColour * offset[4];
////    vec4 sum = vec4(0.0);
////    float blur = radius/resolution;
////
////    float hstep = dir.x;
////    float vstep = dir.y;
////
////    fragColour = vec4(hstep * vstep);
//
////    sum += fragColour(vec2())
//    vec2 offsets[9] = vec2[](
//    vec2(-1,1),
//    vec2( 0.0f,    1), // top-center
//    vec2( 1,  1), // top-right
//    vec2(-1,  0.0f),   // center-left
//    vec2( 0.0f,    0.0f),   // center-center
//    vec2( 1,  0.0f),   // center-right
//    vec2(-1, -1), // bottom-left
//    vec2( 0.0f,   -1), // bottom-center
//    vec2( 1, -1)
//);
//
//    float kernel [9] = float[](
//     1.0/16 , 2.0/16 , 1.0/16 ,
//    2.0/16, 4.0/16, 2.0/16,
//    1.0/16, 2.0/16 , 1.0/16
//    );
//
//    vec3 samTex[9];
//    for (int i = 0; i < 9; i++)
//    {
//        samTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
//    }
//
//    vec3 col = vec3(0.0);
//    for (int i = 0; i < 9; i++)
//    {
//        col += samTex[i] * kernel[i];
//    }
//
//    fragColour = vec4(col, 5.0);
//}

#version 410 core

layout(location=0) out vec4 fragColour;
in vec2 particleColour;
in vec2 TexCoords;
uniform sampler2D screenTexture;

// Define kernel and offsets as uniform arrays
void main()
{
const float kernel[9] = float[](
1.0 / 16, 2.0 / 16, 1.0 / 16,
2.0 / 16, 4.0 / 16, 2.0 / 16,
1.0 / 16, 2.0 / 16, 1.0 / 16
);

const vec2 offsets[9] = vec2[](
vec2(-1,  1), vec2( 0,  1), vec2( 1,  1),
vec2(-1,  0), vec2( 0,  0), vec2( 1,  0),
vec2(-1, -1), vec2( 0, -1), vec2( 1, -1)
);


    vec3 samTex[9];
    for (int i = 0; i < 9; i++)
    {
        samTex[i] = vec3(texture(screenTexture, TexCoords + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += samTex[i] * kernel[i];
    }

    fragColour = vec4(col, 6.0);
}

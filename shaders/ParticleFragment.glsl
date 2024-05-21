#version 410 core

layout(location=0) out vec4 fragColour;
layout(location=1) out vec4 brightColour;
in vec3 particleColour;

uniform sampler2D tex;

void main()
{
    fragColour.rgb = particleColour;
}

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
//
//    fragColour.rgb = particleColour;
//}

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

//#version 410 core
//
//layout(location=0) out vec4 fragColour;
//in vec2 TexCoords;
//uniform sampler2D screenTexture;
//
//void main()
//{
//    const float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16
//    );
//
//    const vec2 offsets[9] = vec2[](
//    vec2(-1,  1), vec2( 0,  1), vec2( 1,  1),
//    vec2(-1,  0), vec2( 0,  0), vec2( 1,  0),
//    vec2(-1, -1), vec2( 0, -1), vec2( 1, -1)
//    );
//
//    vec3 col = vec3(0.0);
//    for (int i = 0; i < 9; i++)
//    {
//        col += texture(screenTexture, TexCoords + offsets[i]).rgb * kernel[i];
//    }
//
//    fragColour = vec4(col, 1.0);
//}



//uniform sampler2D sceneTexture;
//uniform sampler2D depthTexture;
//uniform float focalDistance;
//uniform float focalRange;
//uniform float blurAmount;
//
//in vec2 TexCoords;
//out vec4 FragColor;
//
//void main()
//{
//    // Sample the depth value from the depth texture
//    float depthValue = texture(depthTexture, TexCoords).r;
//
//    // Calculate the distance from the camera to the fragment
//    float cameraDistance = 1.0 / depthValue;
//
//    // Calculate the blur strength based on distance from the focal point
//    float blurStrength = clamp(abs(cameraDistance - focalDistance) / focalRange, 0.0, 1.0);
//
//    // Apply Gaussian blur to the scene texture
//    vec3 color = vec3(0.0);
//    vec2 texelSize = 1.0 / textureSize(sceneTexture, 0);
//    float totalWeight = 0.0;
//    for (float x = -4.0; x <= 4.0; x += 1.0) {
//        for (float y = -4.0; y <= 4.0; y += 1.0) {
//            vec2 offset = vec2(x, y) * texelSize;
//            float weight = exp(-(x * x + y * y) / (2.0 * 4.0 * 4.0));
//            color += texture(sceneTexture, TexCoords + offset).rgb * weight;
//            totalWeight += weight;
//        }
//    }
//    color /= totalWeight;
//
//    FragColor = mix(texture(sceneTexture, TexCoords), vec4(color, 1.0), blurStrength * blurAmount);
//}
//in vec4 vColor;
//in vec2 vTexCoord;
//
//uniform sampler2D u_texture;
//uniform float resolution;
//uniform float radius;
//uniform vec2 dir;
//
//void main() {
//    vec4 sum = vec4(0.0);
//
//    vec2 tc = vTexCoord;
//
//    float blur = radius/resolution;

//    //(1.0, 0.0) -> x-axis blur
//    //(0.0, 1.0) -> y-axis blur
//    float hstep = dir.x;
//    float vstep = dir.y;
//
//    sum += texture2D(u_texture, vec2(tc.x - 4.0*blur*hstep, tc.y - 4.0*blur*vstep)) * 0.0162162162;
//    sum += texture2D(u_texture, vec2(tc.x - 3.0*blur*hstep, tc.y - 3.0*blur*vstep)) * 0.0540540541;
//    sum += texture2D(u_texture, vec2(tc.x - 2.0*blur*hstep, tc.y - 2.0*blur*vstep)) * 0.1216216216;
//    sum += texture2D(u_texture, vec2(tc.x - 1.0*blur*hstep, tc.y - 1.0*blur*vstep)) * 0.1945945946;
//
//    sum += texture2D(u_texture, vec2(tc.x, tc.y)) * 0.2270270270;
//
//    sum += texture2D(u_texture, vec2(tc.x + 1.0*blur*hstep, tc.y + 1.0*blur*vstep)) * 0.1945945946;
//    sum += texture2D(u_texture, vec2(tc.x + 2.0*blur*hstep, tc.y + 2.0*blur*vstep)) * 0.1216216216;
//    sum += texture2D(u_texture, vec2(tc.x + 3.0*blur*hstep, tc.y + 3.0*blur*vstep)) * 0.0540540541;
//    sum += texture2D(u_texture, vec2(tc.x + 4.0*blur*hstep, tc.y + 4.0*blur*vstep)) * 0.0162162162;
//
//    fragColor = vColor * vec4(sum.rgb, 1.0);
//}

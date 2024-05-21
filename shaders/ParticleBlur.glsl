#version 410 core
out vec4 fragColour;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform bool horizontal;

const float weight[5] = float[](
0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216
);

void main()
{
    vec2 tex_offset = 1.0 / textureSize(screenTexture, 0); // gets size of single texel
    vec3 result = fragColour.rgb * weight[4]; // current fragment weight contribution

    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(screenTexture, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(screenTexture, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(screenTexture, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(screenTexture, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }

    fragColour = vec4(result, 1.0);
}

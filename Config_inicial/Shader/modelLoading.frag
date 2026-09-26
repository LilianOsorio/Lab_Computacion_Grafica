#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform bool useTexture;

uniform vec3 objectColor;

void main()
{
    if (useTexture)
    {
        vec4 texColor = texture(texture_diffuse1, TexCoords);

        if (texColor.a < 0.1)
            discard;

        FragColor = texColor;
    }
    else
    {
        FragColor = vec4(objectColor, 1.0);
    }
}
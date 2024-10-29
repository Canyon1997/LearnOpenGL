#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D woodenTexture;
uniform sampler2D happyFaceTexture;
uniform float visibility;

void main()
{
    FragColor = mix(texture(woodenTexture, TexCoord), texture(happyFaceTexture, TexCoord), visibility);

}
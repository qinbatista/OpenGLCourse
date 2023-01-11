#version 330 core

in vec4 vColor;
in vec2 TexCoord;

out vec4 color;
struct  DirectionLight
{
    vec3 color;
    float ambientIntensity;
};

uniform sampler2D theTexture;
uniform DirectionLight directionLight;
void main()
{
    vec4 ambientColor = vec4(directionLight.color, 1.0f)*directionLight.ambientIntensity;
    color = texture(theTexture, TexCoord)*ambientColor;
}
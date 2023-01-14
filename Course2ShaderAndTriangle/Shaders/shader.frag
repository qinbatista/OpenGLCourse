#version 330 core

in vec4 vColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

struct DirectionLight
{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionLight directionLight;
void main()
{
	vec4 ambientColour = vec4(directionLight.color, 1.0f) * directionLight.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionLight.direction)), 0.0f);

	vec4 diffuseColor = vec4(directionLight.color, 1.0f) * directionLight.diffuseIntensity * diffuseFactor;

	color = texture(theTexture, TexCoord) * (ambientColour + diffuseColor);
}
#version 330 core

in vec4 vColor;
in vec2 TexCoord;
flat in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct DirectionLight
{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};
struct Material
{
	float specularIntensity;
	float shininess;
};

uniform sampler2D theTexture;
uniform DirectionLight directionLight;
uniform Material material;

uniform vec3 eyePosition;
void main()
{
	vec4 ambientColour = vec4(directionLight.color, 1.0f) * directionLight.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(directionLight.direction)), 0.0f);

	vec4 diffuseColor = vec4(directionLight.color, 1.0f) * directionLight.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	if (diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(directionLight.direction, normalize(Normal)));
		float specularFactor = max(dot(fragToEye, reflectedVertex), 0.0f);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(directionLight.color * material.specularIntensity, 1.0f) * material.specularIntensity * specularFactor;
		}
	}

	color = texture(theTexture, TexCoord) * (ambientColour + diffuseColor + specularColor);
}
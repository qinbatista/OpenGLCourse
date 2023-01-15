#version 330 core

in vec4 vColor;
in vec2 TexCoord;
flat in vec3 Normal;
in vec3 FragPos;

out vec4 color;
const int MAX_POINT_LIGHTS = 3;
struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};
struct DirectionLight
{
	Light base;
	vec3 direction;
};
struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};
struct Material
{
	float specularIntensity;
	float shininess;
};
uniform int pointLightCount;
uniform DirectionLight directionLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 CalculateByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = vec4(light.color, 1.0f) * light.ambientIntensity;

	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if (diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return ambientColour + diffuseColor + specularColor;
}
vec4 CalcDirectionLight()
{
	return CalculateByDirection(directionLight.base, directionLight.direction);
}
vec4 CalcPointLights()
{
	vec4 totalColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < pointLightCount; i++)
	{
		vec3 direction = FragPos - pointLights[i].position;
		float distance = length(direction);
		direction = normalize(direction);

		vec4 color = CalculateByDirection(pointLights[i].base, direction);
		float attenuation = pointLights[i].exponent * distance * distance + pointLights[i].linear * distance + pointLights[i].constant;
		totalColor += color / attenuation;
	}
	return totalColor;
}
void main()
{
	vec4 finalColor = CalcDirectionLight();
	finalColor += CalcPointLights();
	color = texture(theTexture, TexCoord) * finalColor;
}
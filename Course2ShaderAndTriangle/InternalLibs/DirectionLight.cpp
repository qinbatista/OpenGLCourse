#include "DirectionLight.h"

DirectionLight::DirectionLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}
DirectionLight::DirectionLight(GLfloat red, GLfloat green, GLfloat blue,
							   GLfloat aIntensity, GLfloat dIntensity,
							   GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
}
void DirectionLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
							  GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

DirectionLight::~DirectionLight()
{
}
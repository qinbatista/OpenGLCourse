#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#pragma once
#include "Light.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
class DirectionLight: public Light
{
public:
	DirectionLight();
	DirectionLight(GLfloat red, GLfloat green, GLfloat blue,
					GLfloat aIntensity, GLfloat dIntensity,
					GLfloat xDir, GLfloat yDir, GLfloat zDir);
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
					GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	~DirectionLight();

private:
	glm::vec3 direction;
};

#endif
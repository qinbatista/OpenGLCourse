#ifndef LIGHT_H
#define LIGHT_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#pragma once

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
};

#endif
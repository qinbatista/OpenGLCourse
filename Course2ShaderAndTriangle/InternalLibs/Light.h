#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#pragma once

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
    GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
    GLfloat diffuseIntensityLocation, GLfloat directionLocation);
    ~Light();

private:
    glm::vec3 color;
    GLfloat ambientIntensity;
    glm::vec3 direction;
    GLfloat diffuseIntensity;
};

#endif
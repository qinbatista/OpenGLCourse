#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <GL/glew.h>
#pragma once

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);
    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);
    ~Light();

private:
    glm::vec3 color;
    GLfloat ambientIntensity;
};

#endif
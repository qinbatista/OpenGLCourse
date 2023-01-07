
#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class DisplaySystem
{
public:
    DisplaySystem();
    DisplaySystem(GLfloat aspectRatio);
    void Awake();
    void Update();
    glm::mat4 GetProjection();
    ~DisplaySystem();
    glm::mat4 DisplayProjection;

private:
};
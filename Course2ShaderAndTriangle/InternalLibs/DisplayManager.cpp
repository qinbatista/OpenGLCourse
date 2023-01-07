
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ShaderAndTriangle.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFWManager.h"
glm::mat4 DisplayProjection;
void Awake()
{
    CreateObjects();
    DisplayProjection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    CreateShaders();
}
void Update()
{
    DrawTriangle();
}
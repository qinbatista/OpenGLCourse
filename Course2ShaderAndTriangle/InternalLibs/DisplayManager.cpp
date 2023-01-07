
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ShaderAndTriangle.h"
#include "glm/gtc/matrix_transform.hpp"
glm::mat4 DisplayProjection;
void Awake()
{
    CreateObjects();
    CreateShaders();
    DisplayProjection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
}
void Update()
{
    DrawTriangle();
}
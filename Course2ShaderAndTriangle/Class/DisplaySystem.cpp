#include "DisplaySystem.h"
#include "ShaderAndTriangle.h"
#include "glm/gtc/matrix_transform.hpp"

DisplaySystem::DisplaySystem()
{
    DisplayProjection = glm::perspective(45.0f, (GLfloat)(16 / 9), 0.1f, 100.0f);
}
DisplaySystem::DisplaySystem(GLfloat aspectRatio)
{
    DisplayProjection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
}

void DisplaySystem::Awake()
{
    CreateObjects();
    CreateShaders();
}
void DisplaySystem::Update()
{
    DrawTriangle(DisplayProjection);
}
DisplaySystem::~DisplaySystem()
{
}
#include "DisplaySystem.h"
#include "ShaderAndTriangle.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../InternalLibs/Camera.h"

Camera *displayCamera;

DisplaySystem::DisplaySystem()
{
    DisplayProjection = glm::perspective(45.0f, (GLfloat)(16 / 9), 0.1f, 100.0f);
}
DisplaySystem::DisplaySystem(GLfloat aspectRatio)
{
    DisplayProjection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
}

void DisplaySystem::Awake(Camera *camera)
{
    displayCamera = camera;
    CreateObjects();
    CreateShaders();
}
void DisplaySystem::Update()
{
    DrawTriangle(DisplayProjection,displayCamera);
}
DisplaySystem::~DisplaySystem()
{
}
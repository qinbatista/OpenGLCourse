
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
}
void Update()
{
    DrawTriangle();
}
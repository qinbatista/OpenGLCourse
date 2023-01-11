
#include "ShaderAndTriangle.h"
#include "../InternalLibs/Shader.h"
#include "../InternalLibs/Mesh.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "../InternalLibs/Texture.h"
#include "../InternalLibs/Light.h"
Texture brickTexture;
Texture dirtyTexture;
GLuint uniformModel, uniformProjection, uniformView,uniformAmbientIntensity, uniformAmbientColor;
bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;
const float toRadians = 3.14159265f / 180.0f;
std::vector<Mesh *> meshList;
std::vector<Shader> shaderList;
float curAngle = 0.0f;
float sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;
Light mainLight;
// Fragment Shader
static const char *fShader = "Shaders/shader.frag";
// Vertex Shader
static const char *vShader = "Shaders/shader.vert";

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    uniformModel = shaderList[0].GetModelLocation();
    uniformProjection = shaderList[0].GetProjectionLocation();
}
void CreateObjects()
{
    brickTexture = Texture((char*)"Textures/brick.png");
    brickTexture.LoadTexture();
    dirtyTexture = Texture((char*)"Textures/dirt.png");
    dirtyTexture.LoadTexture();


    mainLight = Light(1.0f, 1.0f,1.0f,0.5f);


    brickTexture.UseTexture();
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};
    GLfloat vertices[] = {
        // x, y, z              u, v
        -1.0f, -1.0f, 0.0f,     0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 1.0f
        };
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj2);
}
void DrawTriangle(glm::mat4 DisplayProjection, glm::mat4 calculateViewMatrix)
{
    if (direction)
        triOffset += triIncrement;
    else
        triOffset -= triIncrement;

    if (abs(triOffset) >= triMaxOffset)
        direction = !direction;
    curAngle += 1.0f;
    if (curAngle > 360)
    {
        curAngle -= 360;
    }
    if (sizeDirection)
        curSize += 0.01f;
    else
        curSize -= 0.01f;

    if (curSize >= maxSize || curSize <= minSize)
        sizeDirection = !sizeDirection;

    shaderList[0].UseShader();
    uniformModel = shaderList[0].GetModelLocation();
    uniformProjection = shaderList[0].GetProjectionLocation();
    uniformView = shaderList[0].GetViewLocation();
    uniformAmbientColor = shaderList[0].GetAmbientColorLocation();
    uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
    mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(triOffset, 0.0f, -3.0f));
    model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(DisplayProjection));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(calculateViewMatrix));
    brickTexture.UseTexture();
    meshList[0]->RenderMesh();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -3.0f));
    model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    dirtyTexture.UseTexture();
    meshList[1]->RenderMesh();

    glUseProgram(0);
}
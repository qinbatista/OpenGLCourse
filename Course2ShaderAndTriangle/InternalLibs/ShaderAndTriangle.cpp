
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "ShaderAndTriangle.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include "DisplayManager.h"
#include "../Class/Mesh.h"
GLuint VAO, VBO, IBO, shader, uniformModel, uniformProjection;
bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;
const float toRadians = 3.14159265f / 180.0f;
std::vector<Mesh*> meshList;

float curAngle = 0.0f;
float sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;
// Vertex Shader
static const char *vShader = " #version 330 core"
                             " layout (location = 0) in vec3 pos;"
                             " out vec4 vColor;"
                             " uniform mat4 model;"
                             " uniform mat4 projection;"
                             " void main()"
                             " {"
                             "      gl_Position = projection * model * vec4(pos, 1.0);"
                             "      vColor = vec4(clamp(pos, 0.0, 1.0), 1.0);"
                             " }";
// Fragment Shader
static const char *fShader = " #version 330 core"
                             " in vec4 vColor;"
                             " out vec4 color;"
                             " void main()"
                             " {"
                             "      color = vColor;"
                             " }";
void CompileShaders()
{
    shader = glCreateProgram();
    if (!shader)
    {
        printf("Shader creation failed!");
        return;
    }
    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);
    GLint result = 0;
    GLchar eLog[1024] = {0};
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }
    glValidateProgram(shader);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }
    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection");

}
void AddShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    const GLchar *theCode[1];
    theCode[0] = shaderCode;
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    GLint result = 0;
    GLchar eLog[1024] = {0};
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: '%sn'", shaderType, eLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}
void CreateTriangle()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2};
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}
void DrawTriangle()
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
    glUseProgram(shader);

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(triOffset, 0.0f, -3.0f));
    // model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
    // glUniform1f(uniformModel, triOffset);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
    meshList[0]->RenderMesh();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-triOffset, 0.0f, -3.0f));
    // model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    meshList[1]->RenderMesh();

    glUseProgram(0);
}

#include "ShaderAndTriangle.h"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/mat4x4.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
GLuint VAO, VBO, shader, uniformModel;
bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;
const float toRadians = 3.14159265f / 180.0f;
float curAngle = 0.0f;
float sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;
// Vertex Shader
static const char *vShader = " #version 330 core"
                             " layout (location = 0) in vec3 pos;"
                             " uniform mat4 model;"
                             " void main()"
                             " {"
                             "      gl_Position = model * vec4(pos, 1.0);"
                             " }";
// Fragment Shader
static const char *fShader = " #version 330 core"
                             " out vec4 color;"
                             " void main()"
                             " {"
                             "      color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
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
    // printf("aaaaaaaaaaaaaa%sn",&vShader);
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
        curSize += 0.001f;
    else
        curSize -= 0.001f;

    if (curSize >= maxSize || curSize <= minSize)
        sizeDirection = !sizeDirection;
    glUseProgram(shader);
    glm::mat4 model(1.0f);
    // model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
    // model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
    // glUniform1f(uniformModel, triOffset);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}
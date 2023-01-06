
#include "ShaderAndTriangle.h"
#include "GL/glew.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
GLuint VAO, VBO, shader, uniformXMove;
bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.0005f;
// Vertex Shader
static const char *vShader = " #version 330 core"
                             " layout (location = 0) in vec3 pos;"
                             " uniform float xMove;"
                             " void main()"
                             " {"
                             "      gl_Position = vec4(1 * pos.x+xMove, 1 * pos.y, pos.z, 1.0);"
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
    uniformXMove = glGetUniformLocation(shader, "xMove");
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
    glUseProgram(shader);
    glUniform1f(uniformXMove, triOffset);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}
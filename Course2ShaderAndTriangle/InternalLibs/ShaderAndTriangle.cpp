
#include "ShaderAndTriangle.h"
#include "GL/glew.h"
#include <stdio.h>
#include <string.h>
GLuint VAO, VBO, _shader;
// Vertex Shader
static const char *vShader = " #version 330 core"
                             " layout (location = 0) in vec3 pos;"
                             " void main()"
                             " {"
                             " gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);"
                             " }";
// Fragment Shader
static const char *fShader = " #version 330 core"
                             " out vec4 color;"
                             " void main()"
                             " {"
                             " color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
                             " }";
void CompileShaders()
{
    _shader = glCreateProgram();
    if (!_shader)
    {
        printf("Shader creation failed!");
        return;
    }
    AddShader(_shader, vShader, GL_VERTEX_SHADER);
    AddShader(_shader, fShader, GL_FRAGMENT_SHADER);
    GLint result = 0;
    GLchar eLog[1024] = {0};
    glLinkProgram(_shader);
    glGetProgramiv(_shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(_shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }
    glValidateProgram(_shader);
    if (!result)
    {
        glGetProgramInfoLog(_shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }
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
    glUseProgram(_shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <string.h>
#include "GLFWManager.h"
GLFWwindow* InitGLFW()
{
    // initialise GLFW
    if (!glfwInit())
    {
        printf("GLFW initialise failed!");
        glfwTerminate();
        return NULL;
    }
    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return NULL;
    }
    // Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);
    return mainWindow;
}
GLint GLFWGetWidth()
{
    return WIDTH;
}
GLint GLFWGetHeight()
{
    return HEIGHT;
}
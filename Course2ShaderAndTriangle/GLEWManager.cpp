#include <stdio.h>
#include <string.h>
#include "GLEWManager.h"
int InitGLEW(GLFWwindow *mainWindow, GLint width, GLint height)
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return true;
    }
    // Setup Viewport size
    glViewport(0, 0, width, height);
    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get and handle user input events
        glfwPollEvents();
        // Clear window
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);
    }
    return false;
}

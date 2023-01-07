#ifndef GLFWManager
#define GLFWManager
#include "GLFW/glfw3.h"
extern GLint WIDTH;
extern GLint HEIGHT;
GLFWwindow *InitGLFW();
GLint GLFWGetWidth();
GLint GLFWGetHeight();
#endif
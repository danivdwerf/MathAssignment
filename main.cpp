#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define APP_NAME "Math Assignment"

int windowWidth = 640;
int windowHeight = 360;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

GLFWwindow* window;

void setupGLFW()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void onWindowResize(GLFWwindow* window, int w, int h)
{
  windowWidth = w;
  windowHeight = h;
  glViewport(0, 0, w, h);
}

void createWindow()
{
  window = glfwCreateWindow(windowWidth, windowHeight, APP_NAME, NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, onWindowResize);
  // glfwSetCursorPosCallback(window, onMouseMove);
  // glfwSetScrollCallback(window, onMouseScroll);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int main(int argc, char* argv[])
{
  setupGLFW();
  createWindow();

  while(!glfwWindowShouldClose(window))
  {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

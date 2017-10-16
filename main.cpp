#include <iostream>
#include <GLFW/glfw3.h>

#include "Assets/_Scripts/Input.h"
#include "Assets/_Scripts/Mat4x4.h"

#define APP_NAME "Math Assignment"

Input* input;
Mat4x4* matrix = new Mat4x4();
Mat4x4* matrix2 = new Mat4x4();

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
  matrix->mat[0][2] = 4;
  matrix->mat[2][3] = 2;
  matrix->mat[1][2] = 6;
  matrix->mat[3][1] = 7;

  matrix2->mat[0][0] = 3;
  matrix2->mat[1][1] = 5;

  std::cout << matrix << '\n' << matrix2 << '\n';
  matrix * *matrix2;
  std::cout << matrix << '\n';
  setupGLFW();
  createWindow();

  input = new Input(window);

  while(!glfwWindowShouldClose(window))
  {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(input->getKeyDown(escape))
      glfwSetWindowShouldClose(window, true);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

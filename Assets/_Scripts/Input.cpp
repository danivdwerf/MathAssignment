#include "Input.h"

GLFWwindow* Input::window;

bool Input::getKeyDown(KeyCode keyCode)
{
  if(window == nullptr)
    return false;

  if (glfwGetKey(window, keyCode) == GLFW_PRESS)
    return true;

  return false;
}

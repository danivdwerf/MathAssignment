#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

class Input
{
  public: enum KeyCode
  {
    space = 32,
    escape = 256,
    a1 = 49,
    a2 = 50,
    a3 = 51,
    a4 = 52,
    a5 = 53,
    a6 = 54,
    a7 = 55,
    a8 = 56,
    a9 = 57,
    a0 = 48,
    a = 65,
    b = 66,
    c = 67,
    d = 68,
    e = 69,
    f = 70,
    g = 71,
    h = 72,
    i = 73,
    j = 74,
    k = 75,
    l = 76,
    m = 77,
    n = 78,
    o = 79,
    p = 80,
    q = 81,
    r = 82,
    s = 83,
    t = 84,
    u = 85,
    v = 86,
    w = 87,
    x = 88,
    y = 89,
    z = 90,
    left = 263,
    right = 262,
    up = 265,
    down = 264
  };
  public: static GLFWwindow* window;
  public: static bool getKeyDown(KeyCode);
};
#endif

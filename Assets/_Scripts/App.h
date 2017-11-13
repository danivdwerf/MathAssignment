#ifndef APP_H
#define APP_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360
#define WINDOW_RESIZE false
#define APP_NAME "Math Assignment"

#include "GUI.h"
#include "Input.h"
#include "Matrix.h"

struct OperatorButton
{
  const char* label;
  GtkWidget* button;
};

class App
{
  private: GtkWidget* window;
  private: GtkWidget* fixed;
  private: GUI* gui;
  private: OperatorButton* buttons;

  public: App(int argc, char* argv[])
  {
    gui = new GUI();
    buttons = new OperatorButton[4];

    gtk_init(&argc, &argv);
  }

  public: void showApp()
  {
    Matrix* mat1 = new Matrix(4,4);
    mat1->mat[0][0] = 4;
    mat1->mat[2][3] = 3;
    mat1->mat[3][3] = 2;
    Matrix* mat2 = new Matrix(4,4);
    mat2->mat[2][1] = 6;
    mat2->mat[0][2] = 2;
    mat2->mat[2][2] = 1;
    mat2->mat[3][3] = 2;

    std::cout << mat1 << '\n';
    std::cout << mat2 << '\n';
    Matrix* temp = mat1->multiply(mat2);
    std::cout << temp << '\n';

    this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RESIZE, APP_NAME, 10);
    this->fixed = gui->createFixed(this->window);

    buttons[0].label = "+";
    buttons[0].button = gui->createButton("+", this->fixed, 20, 20, 20, 20);

    buttons[1].label = "-";
    buttons[1].button = gui->createButton("-", this->fixed, 20, 60, 20, 20);

    buttons[2].label = "*";
    buttons[2].button = gui->createButton("*", this->fixed, 20, 100, 20, 20);

    buttons[3].label = "=";
    buttons[3].button = gui->createButton("=", this->fixed, 20, 140, 20, 20);

    gtk_widget_show_all(window);
    gtk_main();
  }

  public: ~App()
  {
    gtk_main_quit();
  }
};
#endif

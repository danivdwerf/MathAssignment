#ifndef APP_H
#define APP_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360
#define WINDOW_RESIZE false
#define WINDOW_BORDER 10
#define APP_NAME "Math Assignment"

#include <vector>

#include "GUI.h"
#include "Matrix.h"
#include "EntryWidget.h"
#include "Input.h"

struct OperatorButton
{
  const char* label;
  GtkWidget* button;
};

struct InputFieldButton
{
  EntryWidget* widget;
  int width = 5;
  int height = 5;
  int x = 0;
  int y = 0;
};


class App
{
  private: GUI* gui = nullptr;
  private: GtkWidget* window = nullptr;
  private: GtkWidget* fixed = nullptr;

  private: EntryWidget* rowEntry = nullptr;
  private: EntryWidget* columnsEntry = nullptr;
  private: OperatorButton* buttons = nullptr;
  private: InputFieldButton** inputfieldButtons = nullptr;
  private: std::vector<Matrix*>matrices;
  private: std::vector<const char*>operators;

  private: int rows = 2;
  private: int columns = 2;
  private: const gchar* styleSheetPath = "Assets/stylesheet.css";

  public: App(int argc, char* argv[])
  {
    gui = new GUI();
    buttons = new OperatorButton[4];

    this->inputfieldButtons = new InputFieldButton*[this->rows];
    for(int i = 0; i < this->rows; i++)
      this->inputfieldButtons[i] = new InputFieldButton[this->columns];
    gtk_init(&argc, &argv);
  }

  public: void showApp()
  {
    int xPos = 10;
    int yPos = 80;
    int increment = 32;

    this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RESIZE, APP_NAME, WINDOW_BORDER);
    this->fixed = gui->createFixed(this->window);

    const char* rowString = std::to_string(this->rows).c_str();
    const char* columnString = std::to_string(this->columns).c_str();

    this->rowEntry = new EntryWidget(this->fixed, 10, 40, 13, 20, rowString, false);
    this->rowEntry->setText(rowString);

    this->columnsEntry = new EntryWidget(this->fixed, 150, 40, 13, 20, columnString, false);
    this->columnsEntry->setText(columnString);

    generateButtons();
    this->createInputField(xPos, yPos, increment);

    gui->setStyleSheet(styleSheetPath);

    gtk_widget_show_all(window);
    gtk_main();
  }

  private: void generateButtons()
  {
    buttons[0].label = "+";
    buttons[0].button = gui->createButton("+", this->fixed, 290, 80, 20, 20);
    g_signal_connect(buttons[0].button, "clicked", G_CALLBACK(add_callback), this);

    buttons[1].label = "-";
    buttons[1].button = gui->createButton("-", this->fixed, 290, 120, 20, 20);
    g_signal_connect(buttons[1].button, "clicked", G_CALLBACK(substract_callback), this);

    buttons[2].label = "*";
    buttons[2].button = gui->createButton("*", this->fixed, 290, 160, 20, 20);
    g_signal_connect(buttons[2].button, "clicked", G_CALLBACK(multiply_callback), this);

    buttons[3].label = "=";
    buttons[3].button = gui->createButton("=", this->fixed, 290, 200, 20, 20);
    g_signal_connect(buttons[3].button, "clicked", G_CALLBACK(equal_calback), this);
  }

  private: Matrix* fieldToMatrix()
  {
    Matrix* mat = new Matrix(this->rows, this->columns);
    for(int i = 0; i < this->rows; i++)
    {
      for(int j = 0; j < this->columns; j++)
      {
        const char* entryValue = this->inputfieldButtons[i][j].widget->getText();
        if(strlen(entryValue) < 1)
          entryValue = "0";
        int value;
        try
        {
          value = atoi(entryValue);
        }
        catch(const std::exception& e)
        {
          value = 0;
        }
        mat->mat[i][j] = value;
        this->inputfieldButtons[i][j].widget->reset();
      }
    }
    return mat;
  }

  private: void setMatrix(Matrix* mat)
  {
    for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
      {
        int value = mat->mat[i][j];
        this->inputfieldButtons[i][j].widget->setText(std::to_string(value).c_str());
      }
    }
  }

  public: void add()
  {
    Matrix* mat = fieldToMatrix();
    matrices.push_back(mat);
    operators.push_back("+");
  }

  public: void substract()
  {
    Matrix* mat = fieldToMatrix();
    matrices.push_back(mat);
    operators.push_back("-");
  }

  public: void multiply()
  {
    Matrix* mat = fieldToMatrix();
    matrices.push_back(mat);
    operators.push_back("*");
  }

  public: void calculate()
  {
    Matrix* mat = fieldToMatrix();
    matrices.push_back(mat);

    Matrix* temp = matrices[0];
    int size = operators.size();
    for(int i = 0; i < size; i++)
    {
      if(strcmp(operators[i], "+") == 0)
        temp = temp->add(matrices[i+1]);

      if(strcmp(operators[i], "-") == 0)
        temp = temp->subtract(matrices[i+1]);

      if(strcmp(operators[i], "*") == 0)
        temp = temp->multiply(matrices[i+1]);
    }
    this->setMatrix(temp);
  }

  private: static void add_callback(GtkWidget* widget, gpointer* data)
  {
    App* test = reinterpret_cast<App*>(data);
    test->add();
  }

  private: static void substract_callback(GtkWidget* widget, gpointer* data)
  {
    App* test = reinterpret_cast<App*>(data);
    test->substract();
  }

  private: static void multiply_callback(GtkWidget* widget, gpointer* data)
  {
    App* test = reinterpret_cast<App*>(data);
    test->multiply();
  }

  private: static void equal_calback(GtkWidget* widget, gpointer* data)
  {
    App* test = reinterpret_cast<App*>(data);
    test->calculate();
  }

  private: void createInputField(int startXPos, int startYPos, int increment)
  {
    int index = 0;
    int x = startXPos;
    int y = startYPos;
    int inc = increment;

    for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
      {
        this->inputfieldButtons[i][j].widget = new EntryWidget(this->fixed, x, y, this->inputfieldButtons[i][j].width, this->inputfieldButtons[i][j].height, "0");
        index++;
        x += inc*2 + this->inputfieldButtons[i][j].width;

        if(index >= rows)
        {
          y += inc+10;
          index = 0;
          x = startXPos;
        }
        inputfieldButtons[i][j].x = x;
        inputfieldButtons[i][j].y = y;
      }
    }
  }

  public: ~App()
  {
    gtk_main_quit();
  }
};
#endif

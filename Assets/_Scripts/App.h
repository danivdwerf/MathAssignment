#ifndef APP_H
#define APP_H

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 300
#define WINDOW_RESIZE false
#define WINDOW_BORDER 10
#define APP_NAME "Math Assignment"

#include <vector>

#include "GUI.h"
#include "Matrix.h"
#include "EntryWidget.h"

struct OperatorButton
{
  const char* label;
  GtkWidget* button;
};

struct InputFieldButton
{
  EntryWidget* widget;
  int width = 30;
  int height = 23;
  int x = 0;
  int y = 0;
};

class App
{
  private: GUI* gui = nullptr;
  private: GtkWidget* window = nullptr;
  private: GtkWidget* fixed = nullptr;

  private: GtkWidget* scrollWindow = nullptr;
  private: GtkWidget* grid = nullptr;
  private: GtkWidget* rowEntry = nullptr;
  private: GtkWidget* columnsEntry = nullptr;
  private: OperatorButton* buttons = nullptr;
  private: InputFieldButton** inputfieldButtons = nullptr;
  private: std::vector<Matrix*>matrices;
  private: std::vector<const char*>operators;

  private: int rows = 4;
  private: int columns = 4;
  private: const int fieldX = 15;
  private: const int fieldY = 80;
  private: const int entryOffset = 2;

  public: App(int argc, char* argv[])
  {
    this->gui = new GUI();
    this->buttons = new OperatorButton[5];

    this->inputfieldButtons = new InputFieldButton*[this->rows];
    for(int i = 0; i < this->rows; i++)
      this->inputfieldButtons[i] = new InputFieldButton[this->columns];
    gtk_init(&argc, &argv);

    this->setupGUI();
  }

  private: void setupGUI()
  {
    this->window = gui->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_RESIZE, APP_NAME, WINDOW_BORDER);
    this->fixed = gui->createFixed(this->window);

    const char* rowString = std::to_string(this->rows).c_str();
    this->rowEntry = gui->createInputField(rowString, this->fixed, 15, 40, 13);
    g_signal_connect(G_OBJECT(this->rowEntry), "key-press-event", G_CALLBACK(rowChange_callback), this);

    const char* columnString = std::to_string(this->columns).c_str();
    this->columnsEntry = gui->createInputField(columnString, this->fixed, 155, 40, 13);
    g_signal_connect(G_OBJECT(this->columnsEntry), "key-press-event", G_CALLBACK(columnChange_callback), this);

    this->scrollWindow = gui->createScrollWindow(this->fixed, this->fieldX, this->fieldY, 260, 185);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollWindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

    this->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(this->scrollWindow), this->grid);
    gtk_grid_set_row_spacing (GTK_GRID(this->grid), 2);
    gtk_grid_set_column_spacing (GTK_GRID(this->grid), 2);
    gtk_widget_set_name(this->grid, "grid");

    this->createButtons();
    this->createInputField();

    gui->setStyleSheet("Assets/stylesheet.css");
  }

  private: void createButtons()
  {
    buttons[0].label = "+";
    buttons[0].button = gui->createButton("+", this->fixed, 295, 70, 20, 20);
    g_signal_connect(buttons[0].button, "clicked", G_CALLBACK(add_callback), this);

    buttons[1].label = "-";
    buttons[1].button = gui->createButton("-", this->fixed, 295, 110, 20, 20);
    g_signal_connect(buttons[1].button, "clicked", G_CALLBACK(substract_callback), this);

    buttons[2].label = "*";
    buttons[2].button = gui->createButton("*", this->fixed, 295, 150, 20, 20);
    g_signal_connect(buttons[2].button, "clicked", G_CALLBACK(multiply_callback), this);

    buttons[3].label = "=";
    buttons[3].button = gui->createButton("=", this->fixed, 295, 190, 20, 20);
    g_signal_connect(buttons[3].button, "clicked", G_CALLBACK(equal_callback), this);

    buttons[4].label = "C";
    buttons[4].button = gui->createButton("C", this->fixed, 295, 230, 20, 20);
    g_signal_connect(buttons[4].button, "clicked", G_CALLBACK(reset_callback), this);
  }

  private: void createInputField()
  {
    int index = 0;
    int x = this->fieldX;
    int y = this->fieldY;
    int startX = x;

    this->inputfieldButtons = NULL;
    this->inputfieldButtons = new InputFieldButton*[this->rows];
    for(int i = 0; i < this->rows; i++)
      this->inputfieldButtons[i] = new InputFieldButton[this->columns];

    for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
      {
        int currW = this->inputfieldButtons[i][j].width;
        int currH = this->inputfieldButtons[i][j].height;


        this->inputfieldButtons[i][j].widget = new EntryWidget(currW, currH, "0", 24, 14);
        GtkWidget* currWidget = this->inputfieldButtons[i][j].widget->widget;

        gtk_grid_attach(GTK_GRID(this->grid), currWidget, i * currW, j * currH, currW, currH);
      }
    }
    gtk_widget_show_all(this->window);
  }

  private: void emptyField()
  {
    for (int i = 0; i < this->rows; i++)
    {
      for (int j = 0; j < this->columns; j++)
      {
        if(this->inputfieldButtons[i][j].widget != NULL)
          delete this->inputfieldButtons[i][j].widget;
      }
    }
  }

  public: void showApp()
  {

    gtk_widget_show_all(this->window);
    gtk_main();
  }

  public: void onRowChange()
  {
    const char* rowText = gui->getEntryText(this->rowEntry);
    int value;
    try{value = atoi(rowText);}
    catch(const std::exception& e){value = 1;}
    if(value == 0)
      value = 1;
    this->emptyField();
    this->rows = value;
    this->createInputField();
  }

  public: void onColumnChange()
  {
    const char* columnText = gui->getEntryText(this->columnsEntry);
    int value;
    try{value = atoi(columnText);}
    catch(const std::exception& e){value = 1;}
    if(value == 0)
      value = 1;
    this->emptyField();
    this->columns = value;
    this->createInputField();
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
        try{value = atoi(entryValue);}
        catch(const std::exception& e)
        {value = 0;}
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
    this->matrices.push_back(mat);

    Matrix* temp = this->matrices[0];
    int size = operators.size();
    for(int i = 0; i < size; i++)
    {
      if(strcmp(this->operators[i], "+") == 0)
        temp = temp->add(this->matrices[i+1]);

      if(strcmp(this->operators[i], "-") == 0)
        temp = temp->subtract(this->matrices[i+1]);

      if(strcmp(this->operators[i], "*") == 0)
        temp = temp->multiply(this->matrices[i+1]);
    }
    this->matrices.clear();
    this->operators.clear();
    this->matrices[0] = temp;
    this->setMatrix(temp);
  }

  public: void reset()
  {
    Matrix* mat = new Matrix(this->rows, this->columns);
    this->setMatrix(mat);
    this->matrices.clear();
    this->operators.clear();
  }

  private: static void add_callback(GtkWidget* widget, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    app->add();
  }

  private: static void substract_callback(GtkWidget* widget, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    app->substract();
  }

  private: static void multiply_callback(GtkWidget* widget, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    app->multiply();
  }

  private: static void equal_callback(GtkWidget* widget, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    app->calculate();
  }

  private: static void reset_callback(GtkWidget* widget, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    app->reset();
  }

  public: void updateRowEntry(int value)
  {
    gui->setEntryText(this->rowEntry, std::to_string(value).c_str());
  }

  public: void updateColumnEntry(int value)
  {
    gui->setEntryText(this->columnsEntry, std::to_string(value).c_str());
  }

  private: static void rowChange_callback(GtkWidget* widget, GdkEventKey* e, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    if(e->keyval == 0xFF0D)
    {
      app->onRowChange();
      return;
    }

    const char* character = e->string;
    int value = 1;
    try{value = atoi(character);}
    catch(const std::exception& e)
    {value = 1;}
    app->updateRowEntry(value);
  }

  private: static void columnChange_callback(GtkWidget* widget, GdkEventKey* e, gpointer* data)
  {
    App* app = reinterpret_cast<App*>(data);
    if(e->keyval == 0xFF0D)
    {
      app->onColumnChange();
      return;
    }

    const char* character = e->string;
    int value = 1;
    try{value = atoi(character);}
    catch(const std::exception& e)
    {value = 1;}
    app->updateColumnEntry(value);
  }

  public: ~App()
  {
    gtk_main_quit();
  }
};
#endif

#ifndef MATRIX_h
#define MATRIX_h

#include <iostream>
#include <sstream>

class Matrix
{
  public: int** mat;
  public: int r = 0;
  public: int c = 0;

  public: Matrix(int rows, int columns)
  {
    this->r = rows;
    this->c = columns;

    this->mat = new int*[this->r];
    for(int i = 0; i < this->r; i++)
      this->mat[i] = new int[this->c];

    for(int i = 0; i < this->r; i++)
    {
      for(int j = 0; j < this->c; j++)
        this->mat[i][j] = 0;
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Matrix* test)
  {
    std::stringstream ss;
    for(int i = 0; i < test->r; i++)
    {
      ss<<"[";
      for(int j = 0; j < test->c; j++)
      {
        ss<<" " << test->mat[i][j];
      }
      ss<<" ]"<<'\n';
    }
    os << ss.str();
    return os;
  }

  public: Matrix* multiply(Matrix *other)
  {
    Matrix* temp = new Matrix(this->r, other->c);

    for(int i = 0; i < this->r; i++)
    {
      for(int j = 0; j < this->c; j++)
      {
        for(int k = 0; k < other->r; k++)
          temp->mat[i][j] += this->mat[i][k] * other->mat[k][j];
      }
    }
    return temp;
  }

  public: Matrix* add(Matrix* other)
  {
    Matrix* temp = new Matrix(this->r, this->c);
    for(int i = 0; i < temp->r; i++)
    {
      for(int j = 0; j < temp->c; j++)
        temp->mat[i][j] = this->mat[i][j] + other->mat[i][j];
    }
    return temp;
  }

  public: Matrix* subtract(Matrix* other)
  {
    Matrix* temp = new Matrix(this->r, this->c);
    for(int i = 0; i < temp->r; i++)
    {
      for(int j = 0; j < temp->c; j++)
        temp->mat[i][j] = this->mat[i][j] - other->mat[i][j];
    }
    return temp;
  }
};
#endif

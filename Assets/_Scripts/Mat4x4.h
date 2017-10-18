#ifndef MAT4_h
#define MAT4_h

#include <iostream>
#include <sstream>

class Mat4x4
{
  public: int mat[4][4];
  public: Mat4x4()
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
        mat[i][j] = 0;
    }

    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
  }

  friend std::ostream& operator<<(std::ostream& os, const Mat4x4* test)
  {
    std::stringstream ss;
    ss << "[" << test->mat[0][0] << "  " << test->mat[0][1] << "  " << test->mat[0][2] << "  " << test->mat[0][3] << "]" << '\n';
    ss << "[" << test->mat[1][0] << "  " << test->mat[1][1] << "  " << test->mat[1][2] << "  " << test->mat[1][3] << "]" << '\n';
    ss << "[" << test->mat[2][0] << "  " << test->mat[2][1] << "  " << test->mat[2][2] << "  " << test->mat[2][3] << "]" << '\n';
    ss << "[" << test->mat[3][0] << "  " << test->mat[3][1] << "  " << test->mat[3][2] << "  " << test->mat[3][3] << "]" << '\n';
    os << ss.str();
    return os;
  }

  friend Mat4x4* operator*(Mat4x4* original, const Mat4x4& other)
  {
    int pos0_0 = original->mat[0][0] * other.mat[0][0] + original->mat[0][1] * other.mat[1][0] + original->mat[0][2] * other.mat[2][0] + original->mat[0][3] * other.mat[3][0];
    int pos0_1 = original->mat[0][0] * other.mat[0][1] + original->mat[0][1] * other.mat[1][1] + original->mat[0][2] * other.mat[2][1] + original->mat[0][3] * other.mat[3][1];
    int pos0_2 = original->mat[0][0] * other.mat[0][2] + original->mat[0][1] * other.mat[1][2] + original->mat[0][2] * other.mat[2][2] + original->mat[0][3] * other.mat[3][2];
    int pos0_3 = original->mat[0][0] * other.mat[0][3] + original->mat[0][1] * other.mat[1][3] + original->mat[0][2] * other.mat[2][3] + original->mat[0][3] * other.mat[3][3];

    int pos1_0 = original->mat[1][0] * other.mat[0][0] + original->mat[1][1] * other.mat[1][0] + original->mat[1][2] * other.mat[2][0] + original->mat[1][3] * other.mat[3][0];
    int pos1_1 = original->mat[1][0] * other.mat[0][1] + original->mat[1][1] * other.mat[1][1] + original->mat[1][2] * other.mat[2][1] + original->mat[1][3] * other.mat[3][1];
    int pos1_2 = original->mat[1][0] * other.mat[0][2] + original->mat[1][1] * other.mat[1][2] + original->mat[1][2] * other.mat[2][2] + original->mat[1][3] * other.mat[3][2];
    int pos1_3 = original->mat[1][0] * other.mat[0][3] + original->mat[1][1] * other.mat[1][3] + original->mat[1][2] * other.mat[2][3] + original->mat[1][3] * other.mat[3][3];

    int pos2_0 = original->mat[2][0] * other.mat[0][0] + original->mat[2][1] * other.mat[1][0] + original->mat[2][2] * other.mat[2][0] + original->mat[2][3] * other.mat[3][0];
    int pos2_1 = original->mat[2][0] * other.mat[0][1] + original->mat[2][1] * other.mat[1][1] + original->mat[2][2] * other.mat[2][1] + original->mat[2][3] * other.mat[3][1];
    int pos2_2 = original->mat[2][0] * other.mat[0][2] + original->mat[2][1] * other.mat[1][2] + original->mat[2][2] * other.mat[2][2] + original->mat[2][3] * other.mat[3][2];
    int pos2_3 = original->mat[2][0] * other.mat[0][3] + original->mat[2][1] * other.mat[1][3] + original->mat[2][2] * other.mat[2][3] + original->mat[2][3] * other.mat[3][3];

    int pos3_0 = original->mat[3][0] * other.mat[0][0] + original->mat[3][1] * other.mat[1][0] + original->mat[3][2] * other.mat[2][0] + original->mat[3][3] * other.mat[3][0];
    int pos3_1 = original->mat[3][0] * other.mat[0][1] + original->mat[3][1] * other.mat[1][1] + original->mat[3][2] * other.mat[2][1] + original->mat[3][3] * other.mat[3][1];
    int pos3_2 = original->mat[3][0] * other.mat[0][2] + original->mat[3][1] * other.mat[1][2] + original->mat[3][2] * other.mat[2][2] + original->mat[3][3] * other.mat[3][2];
    int pos3_3 = original->mat[3][0] * other.mat[0][3] + original->mat[3][1] * other.mat[1][3] + original->mat[3][2] * other.mat[2][3] + original->mat[3][3] * other.mat[3][3];

    original->mat[0][0] = pos0_0;
    original->mat[0][1] = pos0_1;
    original->mat[0][2] = pos0_2;
    original->mat[0][3] = pos0_3;

    original->mat[1][0] = pos1_0;
    original->mat[1][1] = pos1_1;
    original->mat[1][2] = pos1_2;
    original->mat[1][3] = pos1_3;

    original->mat[2][0] = pos2_0;
    original->mat[2][1] = pos2_1;
    original->mat[2][2] = pos2_2;
    original->mat[2][3] = pos2_3;

    original->mat[3][0] = pos3_0;
    original->mat[3][1] = pos3_1;
    original->mat[3][2] = pos3_2;
    original->mat[3][3] = pos3_3;

    return original;
  }

  friend Mat4x4* operator+(Mat4x4* original, const Mat4x4& other)
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
        original->mat[i][j] = original->mat[i][j] + other.mat[i][j];
    }
    return original;
  }

  friend Mat4x4* operator-(Mat4x4* original, const Mat4x4& other)
  {
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
        original->mat[i][j] = original->mat[i][j] - other.mat[i][j];
    }
    return original;
  }
};
#endif

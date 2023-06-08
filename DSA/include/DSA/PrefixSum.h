#pragma once

#include <vector>

using namespace std;

class NumMatrix {
public:
  vector<vector<int>> v;
  NumMatrix(vector<vector<int>> &matrix) {
    v = vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size()));
    for (int j = 0; j < matrix.size(); j++) {
      v[j][0] = matrix[j][0];
      for (int i = 1; i < matrix[0].size(); i++)
        v[j][i] = matrix[j][i] + v[j][i - 1];
    }
    for (int j = 1; j < matrix.size(); j++)
      for (int i = 0; i < matrix[0].size(); i++)
        v[j][i] += v[j - 1][i];
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return v[row2][col2] - (col1 > 0 ? v[row2][col1 - 1] : 0) - (row1 > 0 ? v[row1 - 1][col2] : 0) +
           (row1 > 0 && col1 > 0 ? v[row1 - 1][col1 - 1] : 0);
  }
};
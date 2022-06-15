// https://leetcode-cn.com/problems/minimize-the-difference-between-target-and-chosen-elements/
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <vector>
using namespace std;

class Solution {
public:
  int minimizeTheDifference(vector<vector<int>> &mat, int target) {
    int m = mat.size();
    int n = mat[0].size();
    vector<bool> possible;
    int SIZE = 1610;
    possible.resize(SIZE);
    for (int i = 0; i < n; i++) {
      possible[mat[0][i]] = true;
    }

    for (int i = 1; i < m; i++) {
      vector<bool> next_possible;
      next_possible.resize(SIZE);
      for (int k = 0; k < SIZE; k++) {
        if (possible[k]) {
          for (int j = 0; j < n; j++) {
            int next = k + mat[i][j];
            if (next < SIZE) {
              next_possible[next] = true;
            }
          }
        }
      }
      possible = next_possible;
    }

    int min_num = INT_MAX;
    for (int i = 0; i < SIZE; i++) {
      if (possible[i]) {
        min_num = min(min_num, abs(i - target));
      }
    }

    if (min_num == INT_MAX) {
      // impossible
      // found min sum
      int sum = 0;
      for (int i = 0; i < m; i++) {
        int local_min = mat[i][0];
        for (int j = 0; j < n; j++) {
          local_min = min(local_min, mat[i][j]);
        }
        sum += local_min;
      }
      return abs(sum - target);
    }

    return min_num;
  }
};
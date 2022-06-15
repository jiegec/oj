// https://leetcode-cn.com/problems/maximum-good-people-based-on-statements/
// 位运算
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  int maximumGood(vector<vector<int>> &statements) {
    int n = statements.size();
    int res = 0;
    for (int good = 0; good < (1 << n); good++) {
      // test validity
      bool valid = true;
      for (int i = 0; i < n && valid; i++) {
        int i_is_good = (good >> i) & 1;
        if (!i_is_good) {
          continue;
        }
        for (int j = 0; j < n; j++) {
          int j_is_good = (good >> j) & 1;
          if (statements[i][j] == 0 && j_is_good) {
            valid = false;
            break;
          }
          if (statements[i][j] == 1 && !j_is_good) {
            valid = false;
            break;
          }
        }
      }

      if (valid) {
        // compute pop count
        int pop = 0;
        for (int i = 0; i < n; i++) {
          if ((good >> i) & 1) {
            pop++;
          }
        }
        if (pop > res) {
          res = pop;
        }
      }
    }
    return res;
  }
};
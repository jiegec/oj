// https://leetcode.cn/problems/check-if-there-is-a-valid-parentheses-string-path/
// 记忆化搜索
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  int m, n;
  bool dfs(vector<vector<char>> &grid, int x, int y, int sum) {
    sum += grid[x][y] == '(' ? 1 : -1;
    if (x == m - 1 && y == n - 1 && sum == 0) {
      return true;
    } else if (sum < 0) {
      return false;
    }

    int dir[2][2] = {{0, 1}, {1, 0}};
    for (int i = 0; i < 2; i++) {
      int xx = x + dir[i][0];
      int yy = y + dir[i][1];
      if (xx >= m || yy >= n) {
        continue;
      }
      if (dfs(grid, xx, yy, sum)) {
        return true;
      }
    }
    return false;
  }
  bool hasValidPath(vector<vector<char>> &grid) {
    vector<vector<set<int>>> map;
    m = grid.size();
    n = grid[0].size();

    map.resize(m);
    for (int i = 0; i < m; i++) {
      map[i].resize(n);
    }

    if (grid[0][0] == ')') {
      return false;
    }

    // return dfs(grid, 0, 0, 0);
    map[0][0].insert(1);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int cur = grid[i][j] == '(' ? 1 : -1;
        if (i > 0) {
          for (auto n : map[i - 1][j]) {
            if (n + cur >= 0) {
              map[i][j].insert(n + cur);
            }
          }
        }
        if (j > 0) {
          for (auto n : map[i][j - 1]) {
            if (n + cur >= 0) {
              map[i][j].insert(n + cur);
            }
          }
        }
      }
    }

    return map[m - 1][n - 1].find(0) != map[m - 1][n - 1].end();
  }
};
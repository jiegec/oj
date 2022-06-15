// https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  int minSessions(vector<int> &tasks, int sessionTime) {
    int n = tasks.size();
    vector<bool> ok;
    ok.resize(1 << n);
    int sum = 0;
    vector<bool> enabled;
    enabled.resize(n);
    for (int i = 0; i < (1 << n); i++) {
      if (sum <= sessionTime) {
        ok[i] = true;
      }

      for (int j = 0; j < n; j++) {
        if (!enabled[j]) {
          enabled[j] = true;
          sum += tasks[j];
          for (int k = 0; k < j; k++) {
            enabled[k] = false;
            sum -= tasks[k];
          }
          break;
        }
      }
    }

    vector<int> dp;
    dp.resize(1 << n);
    for (int i = 1; i < (1 << n); i++) {
      if (ok[i]) {
        dp[i] = 1;
      } else {
        dp[i] = -1;
      }
    }

    for (int i = 1; i < (1 << n); i++) {
      if (dp[i] == -1) {
        // update
        int min_time = n;
        for (int j = 1; j < i; j++) {
          if ((i & j) == j) {
            // subset
            min_time = min(min_time, dp[j] + dp[i & ~j]);
          }
        }
        dp[i] = min_time;
      }
    }

    return dp[(1 << n) - 1];
  }
};
// https://leetcode-cn.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/submissions/
#include <algorithm>
#include <limits.h>
#include <vector>
using namespace std;

class Solution {
public:
  void get_dist(int n, int *data, vector<long long> res[16]) {
    long long cur_sum = 0;
    long long population = 0;
    for (int i = 0; i < (1 << n); i++) {
      res[population].push_back(cur_sum);

      for (int j = 0; j < n; j++) {
        if ((i & (1 << j)) == 0) {
          // find lowest 0
          cur_sum += data[j];
          population += 1;
          for (int k = 0; k < j; k++) {
            cur_sum -= data[k];
            population--;
          }
          break;
        }
      }
    }
  }

  int minimumDifference(vector<int> &nums) {
    long long sum = 0;
    int n = nums.size() / 2;
    for (auto num : nums) {
      sum += num;
    }

    // left n and right n
    vector<long long> left[16];
    get_dist(n, &nums[0], left);
    vector<long long> right[16];
    get_dist(n, &nums[n], right);

    long long right_sum = 0;
    for (int i = n; i < 2 * n; i++) {
      right_sum += nums[i];
    }

    // sort
    for (int i = 0; i <= n; i++) {
      sort(right[i].begin(), right[i].end());
    }

    long long best_ans = LONG_LONG_MAX;
    for (int i = 0; i <= n; i++) {
      // left i, right j
      int j = n - i;
      for (auto l : left[i]) {
        long long target = sum / 2 - l;
        auto it = lower_bound(right[j].begin(), right[j].end(), target);
        if (it != right[j].end()) {
          long long r = *it;
          long long cur_sum = l + r;
          best_ans = min(best_ans, abs(cur_sum - (sum - cur_sum)));
        }

        it = upper_bound(right[j].begin(), right[j].end(), target);
        if (it != right[j].end()) {
          long long r = *it;
          long long cur_sum = l + r;
          best_ans = min(best_ans, abs(cur_sum - (sum - cur_sum)));
        }
      }
    }

    return best_ans;
  }
};
// https://leetcode-cn.com/problems/find-array-given-subset-sums/
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

class Solution {
public:
  vector<int> recoverArray(int n, vector<int> &sums) {
    vector<int> res;
    sort(sums.begin(), sums.end());
    vector<int> temp_sums = sums;
    vector<bool> visit;
    vector<int> new_sums;
    while (res.size() < n) {
      for (int i = 1; i < temp_sums.size(); i++) {
        int step = temp_sums[i] - temp_sums[0];

        visit.clear();
        visit.resize(temp_sums.size());
        new_sums.clear();
        new_sums.reserve(temp_sums.size() / 2);
        new_sums.push_back(temp_sums[0]);
        visit[0] = true;
        visit[i] = true;
        bool fail = false;
        for (int j = 0; j < temp_sums.size(); j++) {
          if (!visit[j]) {
            int k = lower_bound(&temp_sums[j + 1], &temp_sums[temp_sums.size()],
                                temp_sums[j] + step) -
                    &temp_sums[0];
            for (; k < temp_sums.size(); k++) {
              if (temp_sums[k] - temp_sums[j] != step) {
                break;
              } else if (!visit[k]) {
                new_sums.push_back(temp_sums[j]);
                visit[j] = true;
                visit[k] = true;
                break;
              }
            }

            if (!visit[j]) {
              fail = true;
              break;
            }
          }
        }

        if (!fail) {
          temp_sums = new_sums;
          res.push_back(step);
          break;
        }
      }
    }

    assert(res.size() == n);

    long long sum = 0;
    for (int i = 0; i < sums.size(); i++) {
      sum += sums[i];
    }
    sum /= (long long)sums.size() / 2;

    long long cur_sum = 0;
    vector<bool> neg;
    neg.resize(n);
    for (int i = 0; i < n; i++) {
      cur_sum += res[i];
    }

    for (int i = 0; i < 1 << n; i++) {
      if (cur_sum == sum) {
        // found
        break;
      }

      // go to next
      for (int j = 0; j < n; j++) {
        if (!neg[j]) {
          cur_sum -= 2 * res[j];
          neg[j] = true;
          res[j] = -res[j];
          for (int k = 0; k < j; k++) {
            neg[k] = false;
            cur_sum -= 2 * res[k];
            res[k] = -res[k];
          }
          break;
        }
      }
    }
    return res;
  }
};
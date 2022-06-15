// https://codeforces.com/contest/1692/problem/H
#include <algorithm>
#include <map>
#include <stdio.h>
#include <vector>

int x[300000];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    std::map<int, std::vector<int> > index;
    for (int i = 0; i < n; i++) {
      scanf("%d", &x[i]);
      index[x[i]].push_back(i);
    }

    int ans = 1;
    int val = x[0];
    int l = 0;
    int r = 0;

    for (auto &pair : index) {
      int num = pair.first;

      std::vector<int> cost;
      std::vector<int> suffix_max;
      std::vector<int> suffix_max_index;
      int m = pair.second.size();
      suffix_max.resize(m);
      suffix_max_index.resize(m);
      for (int i = 0; i < m; i++) {
        cost.push_back(2 * i - pair.second[i]);
      }

      suffix_max[m - 1] = cost[m - 1];
      suffix_max_index[m - 1] = m - 1;
      for (int i = m - 2; i >= 0; i--) {
        if (cost[i] >= suffix_max[i + 1]) {
          suffix_max_index[i] = i;
        } else {
          suffix_max_index[i] = suffix_max_index[i + 1];
        }
        suffix_max[i] = std::max(suffix_max[i + 1], cost[i]);
      }

      for (int i = 0; i < m - 1; i++) {
        int cur = suffix_max[i + 1] - cost[i] + 1;
        if (cur > ans) {
          ans = cur;
          val = num;
          l = pair.second[i];
          r = pair.second[suffix_max_index[i + 1]];
        }
      }
    }

    printf("%d %d %d\n", val, l + 1, r + 1);
  }
  return 0;
}
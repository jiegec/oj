// https://codeforces.com/contest1690/problem/G
#include <set>
#include <stdio.h>
#include <vector>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);

    std::vector<int> a;
    for (int i = 0; i < n; i++) {
      int num;
      scanf("%d", &num);
      a.push_back(num);
    }

    std::set<int> intervals;
    int cur = a[0];
    int cur_index = 0;
    intervals.insert(0);
    for (int i = 1; i < n; i++) {
      if (a[i] < cur) {
        cur = a[i];
        cur_index = i;
        intervals.insert(i);
      }
    }

    for (int i = 0; i < m; i++) {
      int k, d;
      scanf("%d%d", &k, &d);
      k--;

      a[k] -= d;

      auto it = intervals.upper_bound(k);
      if (it != intervals.begin()) {
        it--;
      }
      if (a[k] < a[*it]) {
        // new interval
        it = intervals.insert(k).first;
      }

      it++;
      while (it != intervals.end()) {
        if (a[*it] < a[k]) {
          break;
        } else {
          auto old_it = it;
          it++;
          intervals.erase(old_it);
        }
      }

      int ans = intervals.size();
      printf("%d ", ans);
    }
    printf("\n");
  }
  return 0;
}
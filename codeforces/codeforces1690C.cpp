// https://codeforces.com/contest/1690/problem/C
#include <stdio.h>
#include <vector>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    std::vector<int> s;
    std::vector<int> f;

    for (int i = 0; i < n; i++) {
      int num;
      scanf("%d", &num);
      s.push_back(num);
    }
    for (int i = 0; i < n; i++) {
      int num;
      scanf("%d", &num);
      f.push_back(num);
    }

    for (int i = 0; i < n; i++) {
      int res;
      if (i == 0) {
        res = f[0] - s[0];
      } else {
        if (s[i] < f[i - 1]) {
          res = f[i] - f[i - 1];
        } else {
          res = f[i] - s[i];
        }
      }
      printf("%d ", res);
    }
    printf("\n");
  }
  return 0;
}
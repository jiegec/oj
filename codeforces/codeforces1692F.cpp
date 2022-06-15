// https://codeforces.com/contest/1692/problem/F
#include <stdio.h>

int a[300000];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    int count[10] = {};
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      a[i] %= 10;
      count[a[i]]++;
    }
    bool found = false;

    for (int i = 0; i < 10 && !found; i++) {
      if (!count[i]) {
        continue;
      }
      for (int j = 0; j < 10 && !found; j++) {
        if (!count[j]) {
          continue;
        } else if (i == j && count[i] < 2) {
          continue;
        }

        int k = (23 - i - j) % 10;
        if (i == j && j == k && count[i] < 3) {
          continue;
        } else if (i == k && count[i] < 2) {
          continue;
        } else if (j == k && count[j] < 2) {
          continue;
        } else if (count[k] < 1) {
          continue;
        }

        found = true;
      }
    }
    printf("%s\n", found ? "YES" : "NO");
  }
  return 0;
}
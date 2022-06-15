// https://codeforces.com/contest/1690/problem/B
#include <algorithm>
#include <stdio.h>

int a[50010];
int b[50010];

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &b[i]);
    }
    bool good = true;
    int diff = -1;

    for (int i = 0; i < n; i++) {
      if (a[i] < b[i]) {
        good = false;
        break;
      }
      if (b[i] != 0) {
        if (diff == -1) {
          diff = a[i] - b[i];
        } else if (diff != a[i] - b[i]) {
          good = false;
          break;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (diff != -1 && b[i] == 0 && a[i] - b[i] > diff) {
        good = false;
        break;
      }
    }

    printf("%s\n", good ? "YES" : "NO");
  }
  return 0;
}
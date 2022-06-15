// https://codeforces.com/contest/1692/problem/D
#include <stdio.h>

bool palin[1440] = {};

int main() {
  for (int i = 0;i < 1440;i++) {
    int h = i / 60;
    int m = i % 60;
    if ((h / 10) == (m % 10) && (h % 10) == (m / 10)) {
      palin[i] = true;
    } else {
      palin[i] = false;
    }
  }

  int t;
  scanf("%d", &t);
  while(t--) {
    int h, m, x;
    scanf("%d:%d %d", &h, &m, &x);
    int time = h * 60 + m;
    int res = palin[time];
    int cur = (time + x) % 1440;
    while(cur != time) {
      if (palin[cur]) {
        res ++;
      }
      cur = (cur + x) % 1440;
    }

    printf("%d\n", res);
  }
  return 0;
}
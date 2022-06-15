#include <map>
#include <stdio.h>

long long d[50240];
long long memo[50240];

long long read() {
  long long data = 0, w = 1;
  char ch = 0;
  while (ch != '-' && (ch < '0' || ch > '9')) {
    ch = getchar();
  }
  if (ch == '-') {
    w = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    data = data * 10 + ch - '0';
    ch = getchar();
  }
  data *= w;
  return data;
}

void write(long long x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) {
    write(x / 10);
  }
  putchar((int)(x % 10 + '0'));
}

int main() {
  long long n, g, r, q;
  scanf("%lld%lld%lld", &n, &g, &r);

  for (int i = 0; i <= n; i++) {
    // scanf("%d", &d[i]);
    d[i] = read();
    memo[i] = 0;
  }
  scanf("%lld", &q);
  while (q--) {
    long long cur = 0;
    scanf("%lld", &cur);
    int depth = -1;
    long long depth_cur = 0;
    for (int i = 0; i < n; i++) {
      cur += d[i];
      long long rem = cur % (g + r);
      if (rem >= g) {
        cur += g + r - rem;
        depth = i;
        depth_cur = cur;
        if (memo[i] != 0) {
          cur += memo[i];
          break;
        }
      } else if (rem == 0) {
        depth = i;
        depth_cur = cur;
        if (memo[i] != 0) {
          cur += memo[i];
          break;
        }
      }
    }
    if (depth != -1 && memo[depth] == 0) {
      memo[depth] = cur - depth_cur;
    }
    cur += d[n];
    // printf("%lld\n", cur);
    write(cur);
    putchar('\n');
  }
}

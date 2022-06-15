#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

struct cp {
  double r, i;
  cp(double rr = 0.0, double ii = 0.0) : r(rr), i(ii) {}
  cp operator+(const cp &o) { return {r + o.r, i + o.i}; }
  cp operator-(const cp &o) { return {r - o.r, i - o.i}; }
  cp operator*(const cp &o) { return {r * o.r - i * o.i, r * o.i + i * o.r}; }
  cp operator/(int n) { return {r / n, i / n}; }
};

class fft {
  int *rev;
  cp *w[2];

public:
  fft(int n) {
    int k, i, L = 0;
    for (k = 1; k < n << 1; k <<= 1, L++)
      ;
    L--;
    rev = (int *)malloc(k * sizeof(int));
    for (i = 1; i < k; i++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << L);
    w[0] = (cp *)malloc((k + 1) * sizeof(cp));
    w[1] = (cp *)malloc((k + 1) * sizeof(cp));
    for (i = 0; i <= k; i++)
      w[1][k - i] = w[0][i] = cp(cos(M_PI * 2 * i / k), sin(M_PI * 2 * i / k));
  }

  void run(cp *a, int n, int r) {
    int i, j, k;
    cp tmp;
    for (i = 1; i < n; i++)
      if (i > rev[i])
        std::swap(a[i], a[rev[i]]);
    for (i = 2; i <= n; i <<= 1)
      for (j = 0; j < n; j += i)
        for (k = 0; k < i >> 1; k++)
          tmp = a[j + k + i / 2] * w[r][n / i * k],
          a[j + k + i / 2] = a[j + k] - tmp, a[j + k] = a[j + k] + tmp;
    if (r)
      for (i = 0; i < n; i++)
        a[i] = a[i] / n;
  }
};

const int Maxn = 133015;
cp a[Maxn], b[Maxn];
char sa[Maxn / 2], sb[Maxn / 2];
int sum[Maxn];
int x1[Maxn], x2[Maxn];

int main() {
  int l1, l2;
  int i;
  fft t(Maxn);
  while (gets(sa)) {
    gets(sb);
    memset(sum, 0, sizeof(sum));
    l1 = strlen(sa);
    l2 = strlen(sb);
    for (i = 0; i < l1; i++)
      x1[i] = sa[l1 - i - 1] - '0';
    for (i = 0; i < l2; i++)
      x2[i] = sb[l2 - i - 1] - '0';

    int len = max(l1, l2), ln;
    for (ln = 0; ln << 1 < len; ln++)
      ;
    len = (++ln) << 1;
    for (i = 0; i < len; i++) {
      if (i > l1)
        a[i] = {0, 0};
      else
        a[i] = {(double)x1[i], 0};
      if (i > l2)
        b[i] = {0, 0};
      else
        b[i] = {(double)x2[i], 0};
    }
    t.run(a, len, 0);
    t.run(b, len, 0);
    for (i = 0; i < len; i++) {
      a[i] = a[i] * b[i];
    }
    t.run(a, len, 1);

    for (i = 0; i < len; i++)
      sum[i] = (int)(a[i].r + 0.5);

    for (i = 0; i < len || sum[i] >= 10; i++) // 进位
    {
      sum[i + 1] += sum[i] / 10;
      sum[i] %= 10;
    }
    len = i;
    while (sum[len] <= 0 && len > 0)
      len--; // 检索最高位
    for (i = len; i >= 0; i--)
      putchar(sum[i] + '0'); // 倒序输出
    putchar('\n');
  }
  return 0;
}

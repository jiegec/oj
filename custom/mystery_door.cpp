#include <stdio.h>
#include <memory.h>


const int MOD = 998244353;
const int MAX = 100024;

int phi[MAX + 1];
int mu[MAX + 1];

void sievePHI() {
  long long i, j;
  for (i = 2; i <= MAX; i++) {
    if (phi[i] == 0) {
      phi[i] = i - 1;
      for (j = i * 2; j <= MAX; j += i) {
        if (phi[j] == 0)phi[j] = j;
        phi[j] /= i;
        phi[j] *= (i - 1);
      }
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  memset(mu, 0, sizeof(mu));
  memset(phi, 0, sizeof(phi));
  mu[1] = 1;

  for (int i = 1; i <= MAX; ++i)
    for (int j = 2 * i; j <= MAX; j += i)
      mu[j] -= mu[i];

  phi[1] = 1;
  sievePHI();
  long long result = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      result += mu[i] * mu[j] * phi[i * j] % MOD;
      result %= MOD;
    }
  }
  printf("%d\n", (int) result);
}

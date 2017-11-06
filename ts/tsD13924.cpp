#include <stdio.h>
char prime[10086] = {0};
int primes[2000] = {0};
int count = 0;
int tens[] = {0,1,10,100,1000,10000,100000,1000000,10000000,100000000};
bool isPan(int num) {
  int n = 1;
  for(;tens[n] <= num;n++);
  if ((n & 1) == 1 && num != 11) {
    return false;
  }
  for (int i = 1;i*2 <= n;i++) {
    if (num / tens[i] % 10 != num / tens[n-i] % 10)
      return false;
  }
  return true;
}
int main() {
  int a, b;
  scanf("%d%d", &a, &b);
  for(int i = 2;i <= 10000;i++) {
    if (prime[i] == 0) {
      prime[i] = 1;
      primes[count++] = i;
      for(int j = i*i;j <= 10000;j += i) prime[j] = 2;
    }
  }
  for (int i = a | 1;i <= b;i+=2) {
    if (i <= 10000) {
      if (prime[i]==1 && isPan(i)) {
        printf("%d\n", i);
      }
    } else if (i > 10000) {
      if (!isPan(i))
        continue;
      int j = 0;
      for (;j < count;j++) {
        if (i % primes[j] == 0) {
          break;
        }
      }
      if (j == count) {
        printf("%d\n", i);
      }
    }
  }
}

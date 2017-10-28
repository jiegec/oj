#include <iostream>
#include <algorithm>
using namespace std;
// 计算 F(n) 和 F(n+1) 除 m 的余数，分别放入 fn 和 fn1 中。
void calcF(int n, int m, int &fn, int &fn1)
{
  // custom code begins
  if (n == 1) {
    fn = fn1 = 1 % m;
  } else if (n == 2) {
    fn = 1 % m;
    fn1 = 2 % m;
  } else {
    int k = n >> 1;
    if (n % 2 == 1) {
      //n = 2k+1
      // g(n) = g(k+1)*g(k+1)+g(k)*g(k)
      // g(n+1) = g(k+2)*g(k+1)+g(k+1)*(g(k+2)-g(k+1))
      int gk,gk1,gk2;
      calcF(k,m,gk,gk1);
      calcF(k+1,m,gk1,gk2);
      fn = ((gk1 * gk1) % m + (gk * gk) % m) % m;
      fn1 = ((gk2 * gk1) % m + (gk1 * (gk2 - gk1 + m)) % m) % m;
    } else {
      // n = 2k;
      // g(n+1) = g(k+1)*g(k+1)+g(k)*g(k)
      // g(n) = g(k+1)*g(k)+g(k)*(g(k+1)-g(k))
      int gk,gk1;
      calcF(k,m,gk,gk1);
      fn1 = ((gk1 * gk1) % m + (gk * gk) % m) % m;
      fn = ((gk1 * gk) % m + (gk * (gk1 - gk + m)) % m) % m;
    }
  }
  // custom code ends
}

int main() {
  int n,m,fn,fn1;
  while(scanf("%d%d",&n,&m) != EOF) {
    calcF(n,m,fn,fn1);
    printf("%d %d\n",fn,fn1);
  }
}

// http://oj.tsinsen.com/D13858
#include <stdio.h>

int fib(int n) {
  if (n == 1 || n == 2)
    return 1;
  return fib(n-1)+fib(n-2);
}

int main() {
  int n;
  while(scanf("%d",&n) && n) {
    int sum = 0;
    for(int i = 1;i <= n;i++) {
      sum += fib(i);
    }
    printf("%d\n",sum);
  }
}

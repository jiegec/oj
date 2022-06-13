// http://oj.tsinsen.com/D14014
#include <stdio.h>
#include <algorithm>

int main() {
  int n;
  scanf("%d",&n);
  int count = 0;
  int num[4];
  while (n != 6174) {
    count++;
    num[0] = n / 1000;
    num[1] = n / 100 % 10;
    num[2] = n / 10 % 10;
    num[3] = n % 10;
    std::sort(num,&num[4]);
    n = - (num[0] * 1000 + num[1] * 100 + num[2] * 10 + num[3]) +
      (num[3] * 1000 + num[2] * 100 + num[1] * 10 + num[0]);
  }
  printf("%d\n",count);
}

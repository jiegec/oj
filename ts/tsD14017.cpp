// http://oj.tsinsen.com/D14017
#include <stdio.h>
#include <algorithm>

int A[10][10];
int permu[10];

int main() {
  int n;
  scanf("%d",&n);
  for (int i = 0;i < n;i++) {
    permu[i] = i;
    for (int j = 0;j < n;j++) {
      scanf("%d",&A[i][j]);
    }
  }
  int res = 0;
  do {
    int sign = 1;
    int ans = 1;
    for (int i = 0;i < n;i++) {
      ans *= A[i][permu[i]];
      for (int j = i+1;j < n;j++) {
        if (permu[i] > permu[j]) {
          sign = -sign;
        }
      }
    }
    ans *= sign;
    res += ans;
  }while (std::next_permutation(permu,permu+n));
  printf("%d\n",res);
}

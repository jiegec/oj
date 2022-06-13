// http://oj.tsinsen.com/D14015
#include <stdio.h>

int b[10] = {0};
int n,k;
int count = 0;

void dfs(int cur) {
  if (cur == k || n == 0) {
    count++;
    b[k] = n;
  } else {
    int nk = n / (k - cur + 1);
    for (int i = 0;i <= nk;i++) {
      b[cur] = i;
      n -= i * (k - cur + 1);
      dfs(cur+1);
      n += i * (k - cur + 1);
    }
  }
}

int main() {
  scanf("%d%d",&n,&k);
  int nk = n/k;
  for (int i = 1;i <= nk;i++) {
    b[1] = i;
    n -= i*k;
    dfs(2);
    n += i*k;
  }
  printf("%d\n",count);
}

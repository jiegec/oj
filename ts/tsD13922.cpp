#include <stdio.h>

const int num = 100086;
int a[num],b[num],c[num],d[num];

int main() {
  int n;
  scanf("%d",&n);
  for(int i = 0;i < n;i++) {
    scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
  }
  int x, y;
  scanf("%d%d",&x,&y);
  int index = -1;
  for(int i = 0;i < n;i++) {
    if (a[i] <= x && a[i]+c[i] >= x && b[i] <= y && b[i]+d[i] >= y) {
      index = i;
    }
  }
  printf("%d\n",index+1);
}

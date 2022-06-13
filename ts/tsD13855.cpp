// http://oj.tsinsen.com/D13855
#include <stdio.h>

int main() {
  int n,Q;
  scanf("%d%d",&n,&Q);
  int num[2000];
  for(int i = 0;i < n;i++) {
    scanf("%d",&num[i]);
  }
  for(int i = 0;i < Q;i++) {
    int lo, hi;
    scanf("%d%d",&lo,&hi);
    int minn = num[lo];
    for(int j = lo+1;j <= hi;j++) {
      if(minn > num[j])
        minn = num[j];
    }
    printf("%d\n",minn);
  }
}

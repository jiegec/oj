// http://oj.tsinsen.com/D13610
#include <stdio.h>

int main() {
  int l,r;
  scanf("%d%d",&l,&r);
  int sum=0;
  for(int i=l;i<=r;i++) {
    int n1=i%10,n2=(i/10)%10,n3=(i/100)%10,n4=(i/1000)%10,n5=(i/10000)%10;
    sum+=n1==2;
    sum+=n2==2;
    sum+=n3==2;
    sum+=n4==2;
    sum+=n5==2;
  }
  printf("%d\n",sum);
}

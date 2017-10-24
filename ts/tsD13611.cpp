#include <stdio.h>

int main() {
  int a,b;
  scanf("%d%d",&a,&b);
  for(int i=a;i<=b;i++) {
    int num=i;
    bool fst=true;
    printf("%d=",num);
    for(int p=2;p<=num;p++){
      if(num % p == 0) {
        num /= p;
        if(fst) {
          printf("%d",p);
          fst = false;
        } else {
          printf("*%d",p);
        }
        p--;
      }
    }
    printf("\n");
  }
}

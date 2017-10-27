#include <stdio.h>
#include <string.h>

char buffer[100086];

inline int hex_to_dec(char c) {
  return c >= 'A' ? c - 'A' + 10 : c - '0';
}
int main() {
  int n;
  scanf("%d",&n);
  while(n--) {
    scanf("%s",buffer);
    int len = strlen(buffer);
    bool first = true;
    if (len % 3 != 0) {
      int num = hex_to_dec(buffer[0]);
      if(len % 3 == 2) {
        num = num * 16 + hex_to_dec(buffer[1]);
      }
      printf("%o",num);
      first = false;
    }
    for (int i = len % 3;i < len;i+=3) {
      int num = hex_to_dec(buffer[i])*256 + hex_to_dec(buffer[i+1])*16 + hex_to_dec(buffer[i+2]);
      if (first) {
        printf("%o",num);
        first = false;
      } else {
        printf("%04o",num);
      }
    }
    printf("\n");
  }
  return 0;
}

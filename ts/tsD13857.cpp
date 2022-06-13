// http://oj.tsinsen.com/D13857
#include <stdio.h>
#include <string.h>
#include <memory.h>

int main() {
  char str1[110],str2[110];
  scanf("%s%s",str1,str2);
  int len1 = strlen(str1), len2 = strlen(str2);
  int num1[110]= {0},num2[110]={0};
  for(int i = 0;i < len1;i++) {
    num1[len1-i-1] = str1[i] - '0';
  }
  for(int i = 0;i < len2;i++) {
    num2[len2-i-1] = str2[i] - '0';
  }
  for(int i = 0;i <= len1 || i <= len2;i++) {
    num1[i] += num2[i];
    num1[i+1] += num1[i] / 10;
    num1[i] %= 10;
  }
  int len = len1 > len2 ? len1 : len2;
  while(num1[len]) {
    len++;
  }
  for(int i = len-1;i >= 0;i--) {
    putchar(num1[i] + '0');
  }
  putchar('\n');
}

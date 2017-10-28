#include <stdio.h>

int main() {
  int count[256] = {0};
  char ch;
  while(scanf("%c",&ch) != EOF) count[ch]++;
  for(char ch = 'a';ch <= 'z';ch++) {
    if(count[ch]) {
      printf("%c %d\n",ch,count[ch]);
    }
  }
}

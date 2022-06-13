// http://oj.tsinsen.com/D13854
#include <stdio.h>

inline char encode(char c) {
  if(('A' <= c && c <= 'Y') || ('a' <= c && c <= 'y'))
    return c+1;
  if(c == 'Z')
    return 'a';
  if(c == 'z')
    return 'A';
  return c;
}

int main() {
  char c;
  while(scanf("%c",&c) != EOF) putchar(encode(c));
}

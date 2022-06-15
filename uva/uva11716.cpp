// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=11716
#include <math.h>
#include <stdio.h>
#include <string.h>

int main() {
  char s[10010];
  int n;
  scanf("%d\n", &n);
  for (int i = 0; i < n; i++) {
    gets(s);
    int len = strlen(s);
    int sqlen = round(sqrt(len));
    if (sqlen * sqlen == len) {
      for (int n = 0; n < sqlen; n++) {
        for (int m = 0; m < sqlen; m++) {
          putchar(s[m * sqlen + n]);
        }
      }
      putchar('\n');
    } else {
      printf("INVALID\n");
    }
  }
}

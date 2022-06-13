// http://oj.tsinsen.com/D13921
#include <stdio.h>
#include <string.h>
#include <memory.h>

int main() {
  char s1[1000], s2[1000];
  fgets(s1, 1000, stdin);
  fgets(s2, 1000, stdin);
  int r = 1;
  s1[strlen(s1)-1] == '\n' ? s1[strlen(s1)-1] = '\0':1;
  s2[strlen(s2)-1] == '\n' ? s2[strlen(s2)-1] = '\0':1;
  if (strlen(s1) == strlen(s2)) {
    if (strcmp(s1, s2) == 0) {
      r = 2;
    } else if (strcasecmp(s1, s2) == 0) {
      r = 3;
    } else {
      r = 4;
    }
  }
  printf("%d\n", r);
}

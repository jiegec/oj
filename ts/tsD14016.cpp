// http://oj.tsinsen.com/D14016
#include <stdio.h>

int hh(int h) {
  if (h == 1) {
    return 1;
  } else if (h == 2) {
    return 2;
  } else if (h == 3) {
    return 4;
  }
  return hh(h-1)+hh(h-2)+hh(h-3);
}

int main() {
  int h;
  scanf("%d",&h);
  if (h < 4 || h > 20) {
    printf("0\n");
  } else {
    printf("%d\n",hh(h));
  }
}

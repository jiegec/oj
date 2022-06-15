// http://oj.tsinsen.com/D13612
#include <stdio.h>

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int num;
    scanf("%d", &num);
    bool fst = true;
    int p = 2;
    for (; p <= num; p++) {
      if (num % p == 0) {
        if (fst && num == p) {
          printf("No\n");
          break;
        } else if (fst && num != p) {
          fst = false;
        } else if (num == p) {
          printf("Yes\n");
          break;
        } else {
          printf("No\n");
          break;
        }
        num /= p;
        p--;
      }
    }
  }
}

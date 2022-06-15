// https://codeforces.com/contest/1692/problem/C
#include <stdio.h>

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    char buffer[1024];
    int i = 0;
    int r = 0;
    int c = 0;
    bool found_two = false;
    while(i < 8) {
      fgets(buffer, sizeof(buffer), stdin);
      if (buffer[0] == '.' || buffer[0] == '#') {
        i++;

        int count = 0;
        int index = 0;
        for (int j = 0;j < 8;j++) {
          if (buffer[j] == '#') {
            count ++;
            index = j;
          }
        }

        if (count == 2) {
          found_two = true;
        }

        if (count == 1 && c == 0 && found_two) {
          c = index + 1;
          r = i;
        }
      }
    }

    printf("%d %d\n", r, c);
  }
	return 0;
}
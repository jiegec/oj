// https://codeforces.com/contest/1697/problem/C
#include <algorithm>
#include <assert.h>
#include <stdio.h>

char s[100010];
char t[100010];

int main() {
  int q;
  scanf("%d", &q);
  while (q--) {
    int n;
    scanf("%d\n", &n);
    fgets(s, sizeof(s), stdin);
    fgets(t, sizeof(t), stdin);

    bool good = true;
    int i = 0, j = 0;
    while (i < n && j < n) {
      if (s[i] == t[j]) {
        i++;
        j++;
        continue;
      } else if (s[i] == 'a' && t[j] == 'b') {
        // find first b forward
        bool found = false;
        for (int k = i; k < n; k++) {
          if (s[k] == 'b') {
            std::swap(s[i], s[k]);
            found = true;
            break;
          } else if (s[k] == 'c') {
            break;
          }
        }
        if (!found) {
          good = false;
          break;
        }

        assert(s[i] == t[j]);
        i++;
        j++;
      } else if (s[i] == 'a' && t[j] == 'c') {
        good = false;
        break;
      } else if (s[i] == 'b' && t[j] == 'a') {
        good = false;
        break;
      } else if (s[i] == 'b' && t[j] == 'c') {
        // find first c forward
        bool found = false;
        for (int k = i; k < n; k++) {
          if (s[k] == 'c') {
            std::swap(s[i], s[k]);
            found = true;
            break;
          } else if (s[k] == 'a') {
            break;
          }
        }
        if (!found) {
          good = false;
          break;
        }

        assert(s[i] == t[j]);
        i++;
        j++;
      } else if (s[i] == 'c' && t[j] == 'a') {
        good = false;
        break;
      } else if (s[i] == 'c' && t[j] == 'b') {
        good = false;
        break;
      }
    }

    printf("%s\n", good ? "YES" : "NO");
  }
  return 0;
}
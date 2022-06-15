// http://poj.org/problem?id=2887
#include <cmath>
#include <cstdio>
#include <cstring>

char block[2][1010][5010];
int current = 0;
int blocks;
int len;
int sqrtlen;
int n[2][1010];
char s[1000010];

int main() {
  // freopen("big.in","r",stdin);
  // freopen("big.out","w",stdout);
  scanf("%s", s);
  len = strlen(s);
  sqrtlen = (int)sqrt(len);
  blocks = ceil((float)len / sqrtlen);
  for (int i = 0; i < blocks; i++) {
    int blocklen = sqrtlen;
    if (i == blocks - 1) {
      blocklen = len - blocks * sqrtlen + sqrtlen;
    }
    n[current][i] = blocklen;
    strncpy(block[current][i], s + i * sqrtlen, blocklen);
  }
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    char op;
    scanf("\n%c", &op);
    if (op == 'Q') {
      int p;
      scanf("%d", &p);
      p--;
      int p1 = 0;
      int i;
      for (i = 0; i < blocks; i++) {
        if (p1 + n[current][i] > p)
          break;
        p1 += n[current][i];
      }
      printf("%c\n", block[current][i][p - p1]);
    } else {
      len++;
      char ch;
      int p;
      scanf(" %c %d", &ch, &p);
      p--;
      int p1 = 0;
      int i;
      for (i = 0; i < blocks; i++) {
        if (p1 + n[current][i] > p)
          break;
        p1 += n[current][i];
      }
      if (i == blocks) {
        block[current][i - 1][n[current][i - 1]] = ch;
        n[current][i - 1]++;
      } else {
        char *s1 = block[current][i] + n[current][i];
        char *s2 = s1 + 1;
        char *begin = &block[current][i][p - p1];
        while (s1 >= begin) {
          *s2 = *s1;
          s2--;
          s1--;
        }
        block[current][i][p - p1] = ch;
        n[current][i]++;
      }

      if (n[current][i] >= 5000) {
        sqrtlen = (int)sqrt(len);
        blocks = ceil((float)len / sqrtlen);
        int currentblock = 0;
        int currentpos = 0;
        for (int i = 0; i < blocks; i++) {
          int blocklen = sqrtlen;
          if (i == blocks - 1) {
            blocklen = len - blocks * sqrtlen + sqrtlen;
          }
          n[!current][i] = blocklen;
          for (int j = 0; j < blocklen; j++) {
            block[!current][i][j] = block[current][currentblock][currentpos];
            currentpos++;
            if (currentpos == n[current][currentblock]) {
              currentpos = 0;
              currentblock++;
            }
          }
        }
        current = !current;
      }
    }
  }
}

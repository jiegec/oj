// http://poj.org/problem?id=1185
// 状压DP
// http://blog.csdn.net/accry/article/details/6607703
#include <stdio.h>
#include <string.h>

int N, M;
char MAP[110][20];
int STATE[70], TOP;
int ROW[110], NUM[110];
int DP[110][70][70];

inline int max(int a, int b) { return a > b ? a : b; }

int count(int x) {
  int cnt = 0;
  while (x) {
    cnt++;
    x &= (x - 1);
  }
  return cnt;
}

int main() {
  while (scanf("%d%d", &M, &N) != EOF) {
    if (N == 0 && M == 0)
      break;
    TOP = 0;
    for (int i = 0; i < (1 << N); i++) {
      if (i & (i << 1))
        continue;
      if (i & (i << 2))
        continue;
      STATE[TOP++] = i;
    }
    for (int i = 0; i < M; i++) {
      scanf("%s", MAP[i]);
    }
    for (int i = 0; i < M; i++) {
      ROW[i] = 0;
      for (int j = 0; j < N; j++) {
        if (MAP[i][j] == 'H')
          ROW[i] += (1 << (N - j - 1));
      }
    }
    memset(DP, -1, sizeof(DP));
    for (int i = 0; i < TOP; i++) {
      NUM[i] = count(STATE[i]);
      if (STATE[i] & ROW[0])
        continue;
      DP[0][0][i] = NUM[i];
    }

    for (int i = 1; i < M; i++) {
      for (int t = 0; t < TOP; t++) {
        if (STATE[t] & ROW[i])
          continue;
        for (int j = 0; j < TOP; j++) {
          if (STATE[t] & STATE[j])
            continue;
          for (int k = 0; k < TOP; k++) {
            if (STATE[t] & STATE[k])
              continue;
            if (DP[i - 1][j][k] != -1)
              DP[i][k][t] = max(DP[i][k][t], DP[i - 1][j][k] + NUM[t]);
          }
        }
      }
    }

    int ans = 0;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < TOP; j++) {
        for (int k = 0; k < TOP; k++) {
          ans = max(ans, DP[i][j][k]);
        }
      }
    }
    printf("%d\n", ans);
  }
}

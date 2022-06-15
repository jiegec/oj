// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=10181
#include <cstdio>
#define P(i, j) ((i) << 2 | (j))
int bound, loc_1[16][2] = {3, 3, 0, 0, 0, 1, 0, 2, 0, 3, 1, 0, 1, 1, 1, 2,
                           1, 3, 2, 0, 2, 1, 2, 2, 2, 3, 3, 0, 3, 1, 3, 2};
bool flag;
int p[127];
char d[] = {'U', 'D', 'L', 'R'};

inline int abs(int a) { return a > 0 ? a : -a; }

inline int min(int a, int b) { return a > b ? b : a; }

#define UNROLL(i, j)                                                           \
  if (a[P(i, j)]) {                                                            \
    sum1 += abs((i)-loc_1[a[P(i, j)]][0]) + abs((j)-loc_1[a[P(i, j)]][1]);     \
  }

struct D {
  int pos, a[16];
  int H() {
    int sum1 = 0;
    UNROLL(0, 0);
    UNROLL(0, 1);
    UNROLL(0, 2);
    UNROLL(0, 3);
    UNROLL(1, 0);
    UNROLL(1, 1);
    UNROLL(1, 2);
    UNROLL(1, 3);
    UNROLL(2, 0);
    UNROLL(2, 1);
    UNROLL(2, 2);
    UNROLL(2, 3);
    UNROLL(3, 0);
    UNROLL(3, 1);
    UNROLL(3, 2);
    UNROLL(3, 3);
    return sum1;
  }
} s;

#define ins(x0, y0, dir)                                                       \
  {                                                                            \
    s.pos = np = P(x0, y0), s.a[op] = s.a[np], s.a[np] = 0,                    \
    tmp = dfs(x + 1, dir);                                                     \
    if (flag)                                                                  \
      return p[x] = (dir), tmp;                                                \
    if (nxt > tmp)                                                             \
      nxt = tmp;                                                               \
    s.a[np] = s.a[op], s.a[op] = 0;                                            \
  }

int dfs(int x, int las) {
  int hv = s.H();
  if (x + hv > bound)
    return x + hv;
  if (hv == 0)
    return flag = true, x;
  int op = s.pos, zx = op >> 2, zy = op & 3, nxt = 127, tmp, np;
  if (zx > 0 && las != 1)
    ins(zx - 1, zy, 0);
  if (zy > 0 && las != 3)
    ins(zx, zy - 1, 2);
  if (zx < 3 && las != 0)
    ins(zx + 1, zy, 1);
  if (zy < 3 && las != 2)
    ins(zx, zy + 1, 3);
  return s.pos = op, nxt;
}

int main() {
  int N;
  scanf("%d", &N);
  while (N--) {
    flag = false;
    int zero_row = 0;
    for (int i = 0; i < 16; i += 4)
      for (int j = 0; j < 4; j++) {
        scanf("%d", &s.a[i | j]);
        if (s.a[i | j] == 0)
          s.pos = i | j, zero_row = i / 4 + 1;
      }
    int sum = 0;
    for (int i = 0; i < 16; i++) {
      if (s.a[P(i / 4, i % 4)] == 0)
        continue;
      for (int j = i; j < 16; j++) {
        if (s.a[P(j / 4, j % 4)] < s.a[P(i / 4, i % 4)] &&
            s.a[P(j / 4, j % 4)] != 0)
          sum++;
      }
    }
    if ((sum + zero_row) & 1) {
      printf("This puzzle is not solvable.\n");
      continue;
    }
    for (bound = s.H(); !flag; bound = dfs(0, -1))
      ;
    for (int i = 0; i < bound; i++)
      putchar(d[p[i]]);
    putchar('\n');
  }
  return 0;
}

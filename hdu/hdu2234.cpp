// http://acm.hdu.edu.cn/showproblem.php?pid=2234
#include <cstdio>
int bound;
bool flag;
int rot[][4] = {
    {0, 1, 2, 3},   {3, 2, 1, 0},   {4, 5, 6, 7},     {7, 6, 5, 4},
    {8, 9, 10, 11}, {11, 10, 9, 8}, {12, 13, 14, 15}, {15, 14, 13, 12},
    {0, 4, 8, 12},  {12, 8, 4, 0},  {1, 5, 9, 13},    {13, 9, 5, 1},
    {2, 6, 10, 14}, {14, 10, 6, 2}, {3, 7, 11, 15},   {15, 11, 7, 3}};

inline int max(int a, int b) { return a > b ? a : b; }

inline int min(int a, int b) { return a < b ? a : b; }

struct D {
  int a[16];
  int H() {
    int n[5] = {0};
    int m1 = 0, m2 = 0;
    for (int i = 0; i < 4; i++) {
      n[1] = n[2] = n[3] = n[4] = 0;
      for (int j = 0; j < 4; j++) {
        n[a[i << 2 | j]]++;
      }
      int ma = 0;
      ma = max(ma, n[1]);
      ma = max(ma, n[2]);
      ma = max(ma, n[3]);
      ma = max(ma, n[4]);
      m1 += 4 - ma;

      n[1] = n[2] = n[3] = n[4] = 0;
      for (int j = 0; j < 4; j++) {
        n[a[j << 2 | i]]++;
      }
      int mb = 0;
      mb = max(mb, n[1]);
      mb = max(mb, n[2]);
      mb = max(mb, n[3]);
      mb = max(mb, n[4]);
      m2 += 4 - mb;
    }
    return (min(m1, m2) + 3) >> 2;
  }
} s;

void rotate(int dir) {
  int temp = s.a[rot[dir][3]];
  // for(int i=2;i>=0;i--) {
  //   s.a[rot[dir][i+1]] = s.a[rot[dir][i]];
  // }
  s.a[rot[dir][3]] = s.a[rot[dir][2]];
  s.a[rot[dir][2]] = s.a[rot[dir][1]];
  s.a[rot[dir][1]] = s.a[rot[dir][0]];
  s.a[rot[dir][0]] = temp;
}

#define inc(dir, rev)                                                          \
  {                                                                            \
    rotate(dir);                                                               \
    tmp = dfs(x + 1, dir);                                                     \
    if (flag)                                                                  \
      return tmp;                                                              \
    if (nxt > tmp)                                                             \
      nxt = tmp;                                                               \
    rotate(rev);                                                               \
  }

int dfs(int x, int las) {
  int hv = s.H();
  if (x + hv > bound)
    return x + hv;
  if (hv == 0)
    return flag = true, x;
  int nxt = 0x7FFF, tmp;
  for (int i = 0; i < 16; i++) {
    if ((i ^ las) != 1) {
      inc(i, i ^ 1);
    }
  }
  return nxt;
}

int main() {
  int N;
  scanf("%d", &N);
  while (N--) {
    flag = false;
    for (int i = 0; i < 16; i++) {
      scanf("%d", &s.a[i]);
    }
    for (bound = s.H(); !flag && bound <= 5; bound = dfs(0, -1))
      ;
    if (bound > 5) {
      printf("-1\n");
    } else {
      printf("%d\n", bound);
    }
  }
}

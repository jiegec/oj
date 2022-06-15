// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=10603
#include <queue>
#include <stdio.h>
#include <string.h>

using namespace std;

struct state {
  int x;
  int y;
  int z;
  int sum;
};

bool operator<(state a, state b) { return a.sum > b.sum; }

const int MAX = 0xfffffff;

int minsum[210][210][210];
int mind[210];

int main() {
  int t, a, b, c, d;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int i = 0; i <= a + 1; i++)
      for (int j = 0; j <= b + 1; j++)
        for (int k = 0; k <= c + 1; k++)
          minsum[i][j][k] = MAX;
    for (int i = 0; i < 201; i++)
      mind[i] = MAX;
    state start;
    start.x = start.y = 0;
    start.z = c;
    start.sum = 0;
    queue<state> pq;
    minsum[0][0][c] = 0;
    mind[c] = 0;
    mind[0] = 0;
    pq.push(start);
    while (!pq.empty()) {
      state current = pq.front();
      pq.pop();
      mind[current.x] = min(mind[current.x], current.sum);
      mind[current.y] = min(mind[current.y], current.sum);
      mind[current.z] = min(mind[current.z], current.sum);
      if (current.sum > mind[d]) {
        continue;
      }

      int xtoy = min(current.x, b - current.y);
      if (xtoy > 0) {
        state temp = current;
        temp.x -= xtoy;
        temp.y += xtoy;
        temp.sum += xtoy;
        if (minsum[temp.x][temp.y][temp.z] > temp.sum) {
          minsum[temp.x][temp.y][temp.z] = temp.sum;
          pq.push(temp);
        }
      }

      int ytoz = min(current.y, c - current.z);
      if (ytoz > 0) {
        state temp = current;
        temp.y -= ytoz;
        temp.z += ytoz;
        temp.sum += ytoz;
        if (minsum[temp.x][temp.y][temp.z] > temp.sum) {
          minsum[temp.x][temp.y][temp.z] = temp.sum;
          pq.push(temp);
        }
      }

      int ztox = min(current.z, a - current.x);
      if (ztox > 0) {
        state temp = current;
        temp.z -= ztox;
        temp.x += ztox;
        temp.sum += ztox;
        if (minsum[temp.x][temp.y][temp.z] > temp.sum) {
          minsum[temp.x][temp.y][temp.z] = temp.sum;
          pq.push(temp);
        }
      }

      int xtoz = min(current.x, c - current.z);
      if (xtoz > 0) {
        state temp = current;
        temp.x -= xtoz;
        temp.z += xtoz;
        temp.sum += xtoz;
        if (minsum[temp.x][temp.y][temp.z] > temp.sum) {
          minsum[temp.x][temp.y][temp.z] = temp.sum;
          pq.push(temp);
        }
      }

      int ytox = min(current.y, a - current.x);
      if (ytox > 0) {
        state temp = current;
        temp.y -= ytox;
        temp.x += ytox;
        temp.sum += ytox;
        if (minsum[temp.x][temp.y][temp.z] > temp.sum) {
          minsum[temp.x][temp.y][temp.z] = temp.sum;
          pq.push(temp);
        }
      }

      int ztoy = min(current.z, b - current.y);
      if (ztoy > 0) {
        state temp = current;
        temp.z -= ztoy;
        temp.y += ztoy;
        temp.sum += ztoy;
        if (minsum[temp.x][temp.y][temp.z] > temp.sum) {
          minsum[temp.x][temp.y][temp.z] = temp.sum;
          pq.push(temp);
        }
      }
    }
    for (int i = d; i >= 0; i--) {
      if (mind[i] != MAX) {
        printf("%d %d\n", mind[i], i);
        break;
      }
    }
  }
}

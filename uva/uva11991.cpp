// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=11991
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;

map<int, vector<int>> t;

int main() {
  int n, m, k, v, num;
  while (scanf("%d%d", &n, &m) != EOF) {
    t.clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d", &num);
      t[num].push_back(i);
    }
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &k, &v);
      if (t[v].size() < k) {
        printf("0\n");
      } else {
        printf("%d\n", t[v][k - 1]);
      }
    }
  }
}

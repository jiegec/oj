// http://uoj.ac/problem/16
#include <algorithm>
#include <stdio.h>
#include <vector>
using namespace std;

vector<int> adj[200010];
int quan[200010];

int main() {
  int n, a, b;
  long long sum = 0, maxquan = 0;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++) {
    scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &quan[i]);
  }
  for (int i = 1; i <= n; i++) {
    long long sumadj = 0;
    long long sumsqr = 0;
    if (adj[i].size() < 2) {
      continue;
    }
    long long firstmax = max(quan[adj[i][0]], quan[adj[i][1]]);
    long long secondmax = min(quan[adj[i][0]], quan[adj[i][1]]);
    // Lets belive in -O :)
    for (int j = 0; j < adj[i].size(); j++) {
      sumadj += quan[adj[i][j]];
      sumsqr += quan[adj[i][j]] * quan[adj[i][j]];
      if (j > 1) {
        if (quan[adj[i][j]] > firstmax) {
          secondmax = firstmax;
          firstmax = quan[adj[i][j]];
        } else if (quan[adj[i][j]] > secondmax) {
          secondmax = quan[adj[i][j]];
        }
      }
    }
    long long current = sumadj * sumadj - sumsqr;
    maxquan = max(maxquan, firstmax * secondmax);
    sum += current;
  }
  printf("%lld %lld\n", maxquan, sum % 10007);
}

// https://codeforces.com/contest/1695/problem/D
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <memory.h>

int edge_from[2048], edge_to[2048];
int visit[2048];
std::vector<std::vector<int>> adj;

int dfs(int root) {
  assert(!visit[root]);
  visit[root] = true;

  std::vector<int> results;
  for (int i = 0; i < adj[root].size(); i++) {
    if (visit[adj[root][i]]) {
      continue;
    }
    results.push_back(dfs(adj[root][i]));
  }

  int sum = 0;
  int zero_tree = 0;
  for (int i = 0; i < results.size(); i++) {
    sum += results[i];
    zero_tree += results[i] == 0;
  }

  visit[root] = false;
  return sum + std::max(0, zero_tree - 1);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
      scanf("%d%d", &edge_from[i], &edge_to[i]);
      edge_from[i]--;
      edge_to[i]--;
    }
    adj.clear();
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
      adj[edge_from[i]].push_back(edge_to[i]);
      adj[edge_to[i]].push_back(edge_from[i]);
    }

    if (n == 1) {
      printf("%d\n", 0);
      continue;
    }

    memset(visit, 0, sizeof(visit));
    int ans = 20000;
    for (int i = 0; i < n; i++) {
      ans = std::min(ans, dfs(i));
    }
    printf("%d\n", ans + 1);
  }
  return 0;
}
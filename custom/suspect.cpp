#include <cstring>
#include <math.h>
#include <queue>
#include <stdio.h>
#include <utility>

#define ll long long

int n, m;
ll dist[30010] = {0};
double ln_dist[30010] = {0};
ll edges[60010] = {0};
ll ww[60010] = {0};
double ln_ww[60010] = {0};
ll fst[60010] = {0};
ll nxt[60010] = {0};
bool vis[30010] = {false};
ll num = 0;

void dfs(ll cur) {
  vis[cur] = true;
  if (cur == n)
    return;
  for (ll p = fst[cur]; p; p = nxt[p]) {
    ll y = edges[p];
    if (!vis[y] || ln_dist[cur] + ln_ww[p] < ln_dist[y]) {
      ln_dist[y] = ln_dist[cur] + ln_ww[p];
      dist[y] = dist[cur] * ww[p] % 23333;
      dfs(y);
    }
  }
}

void dijkstra() {
  vis[1] = true;
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>,
                      std::greater<std::pair<double, int>>>
      pq;
  pq.push(std::pair<double, int>(0.0, 1));
  while (!pq.empty()) {
    std::pair<double, int> pp = pq.top();
    pq.pop();
    int u = pp.second;
    vis[u] = true;
    for (ll p = fst[u]; p; p = nxt[p]) {
      ll y = edges[p];
      if (!vis[y]) {
        if (ln_dist[u] + ln_ww[p] < ln_dist[y]) {
          ln_dist[y] = ln_dist[u] + ln_ww[p];
          dist[y] = dist[u] * ww[p] % 23333;
          pq.push(std::pair<double, int>(ln_dist[y], y));
        }
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    dist[i] = 10000000000, ln_dist[i] = 10000000000.0;
  dist[1] = 1, ln_dist[1] = 0.0;
  for (int i = 0; i < m; i++) {
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    edges[++num] = y;
    ww[num] = w + 1;
    ln_ww[num] = log(ww[num]);
    nxt[num] = fst[x];
    fst[x] = num;

    edges[++num] = x;
    ww[num] = w + 1;
    ln_ww[num] = log(ww[num]);
    nxt[num] = fst[y];
    fst[y] = num;
  }
  dijkstra();
  printf("%lld\n", dist[n] % 23333);
}

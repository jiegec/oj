#include <stdio.h>

#define ll long long

inline ll max(ll a, ll b) { return a > b ? a : b; }
ll n, m;
ll edge_num[2000], edges[2000][2000], w[2000][2000];
ll dist[2000] = {0};
ll cycle[2000] = {0}, cycle_num = 0;
ll big_cycle[2000] = {0};

void dfs(ll cur) {
  for (ll i = 0; i < edge_num[cur]; i++) {
    if (dist[edges[cur][i]] == 0) {
      dist[edges[cur][i]] = dist[cur] ^ w[cur][i];
      dfs(edges[cur][i]);
    } else {
      cycle[cycle_num++] = (dist[edges[cur][i]] ^ dist[cur]) ^ w[cur][i];
    }
  }
}

int main() {
  scanf("%lld%lld", &n, &m);
  for (ll i = 0; i < m; i++) {
    ll a, b, ww;
    scanf("%lld%lld%lld", &a, &b, &ww);
    edges[a][edge_num[a]++] = b;
    edges[b][edge_num[b]++] = a;
    w[a][edge_num[a] - 1] = w[b][edge_num[b] - 1] = ww;
  }
  dfs(1);
  for (ll i = 0; i < cycle_num; i++) {
    for (ll j = 63; j >= 0; j--) {
      if (cycle[i] & (1 << j)) {
        if (big_cycle[j] == 0) {
          big_cycle[j] = cycle[i];
          break;
        } else {
          cycle[i] ^= big_cycle[j];
        }
      }
    }
  }
  ll res = dist[n];
  for (ll j = 63; j >= 0; j--) {
    res = max(res, res ^ big_cycle[j]);
  }
  printf("%lld\n", res);
  return 0;
}

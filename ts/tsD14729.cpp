// http://oj.tsinsen.com/D14729
#include <memory.h>
#include <queue>
#include <stdio.h>
#include <string.h>

const static int INF = 1 << 30;

int n;
// 1~n: set
int num_edges[700] = {0};
int edges[700][700] = {{0}};
int matching[700] = {0};
int visit[700] = {0};

// 0: source
// n+1: sink
struct edge {
  int to;
  int next_edge;
  int residue;
} edges_flow[500 * 500 * 2];
int top = 1;
int top_edges_flow[700] = {0};

int weight[500] = {0};
int depth[500] = {0};
int map_set[500] = {0};

inline int min(int a, int b) { return a > b ? b : a; }

void add_edge(int from, int to, int cap) {
  edges_flow[++top] = edge{to, top_edges_flow[from], cap};
  top_edges_flow[from] = top;
  edges_flow[++top] = edge{from, top_edges_flow[to], 0};
  top_edges_flow[to] = top;
}

bool match(int cur) {
  for (int i = 0; i < num_edges[cur]; i++) {
    int another = edges[cur][i];
    if (visit[another] == 0) {
      visit[another] = 1;
      if (matching[another] == 0 || match(matching[another])) {
        matching[another] = cur;
        return true;
      }
    }
  }

  return false;
}

bool bfs() {
  for (int i = 0; i <= n + 1; i++) {
    depth[i] = -1;
  }
  std::queue<int> que;
  que.push(0);
  depth[0] = 0;
  while (!que.empty()) {
    int current = que.front();
    que.pop();
    for (int i = top_edges_flow[current]; i != 0; i = edges_flow[i].next_edge) {
      int next = edges_flow[i].to;
      if (edges_flow[i].residue > 0 && depth[next] < 0) {
        depth[next] = depth[current] + 1;
        que.push(next);
      }
    }
  }
  return depth[n + 1] > 0;
}

int dfs(int current, int to, int current_flow) {
  if (current == to || current_flow == 0) {
    return current_flow;
  }

  int flow = 0;
  for (int i = top_edges_flow[current]; i != 0; i = edges_flow[i].next_edge) {
    int next = edges_flow[i].to;
    if (edges_flow[i].residue > 0 && depth[next] == depth[current] + 1) {
      int result =
          dfs(next, to, min(edges_flow[i].residue, current_flow - flow));
      if (result) {
        flow += result;
        edges_flow[i].residue -= result;
        edges_flow[i ^ 1].residue += result;
        if (flow == current_flow) {
          return flow;
        }
      }
    }
  }
  if (flow == 0) {
    depth[current] = -1;
  }
  return flow;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &num_edges[i]);
    for (int j = 0; j < num_edges[i]; j++) {
      scanf("%d", &edges[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &weight[i]);
    // Find minimum instead of maximum
    weight[i] = -weight[i];
  }
  // Perfect Matching
  for (int i = 1; i <= n; i++) {
    memset(visit, 0, sizeof(visit));
    match(i);
  }
  // Maximum flow
  int positive_weight = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < num_edges[i]; j++) {
      // if i is covered, then
      // all numbers in i should be covered,
      // link those corresponding sets
      // if (matching[edges[i][j]] != i)
      add_edge(i, matching[edges[i][j]], INF);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (weight[i] < 0) {
      // link to sink
      add_edge(i, n + 1, -weight[i]);
    } else {
      add_edge(0, i, weight[i]);
      positive_weight += weight[i];
    }
  }
  int max_flow = 0;
  while (bfs()) {
    max_flow += dfs(0, n + 1, INF);
  }
  printf("%d\n", max_flow - positive_weight);
  return 0;
}

// http://poj.org/problem?id=2421
#include <stdio.h>
#include <algorithm>

using namespace std;

struct node {
  int father;
  int childnum;
};

struct edge {
  int a;
  int b;
  int dist;
};

node nodes[110];

edge edges[10086];

int edge_num;

int n;

int get_father(int n) {
  return nodes[n].father == n ?
         n : (nodes[n].father = get_father(nodes[n].father));
}

bool cmp(edge a, edge b) {
  return a.dist < b.dist;
}

bool merge(int a, int b) {
  a = get_father(a);
  b = get_father(b);
  nodes[a].father = b;
  nodes[b].childnum += nodes[a].childnum;
  return nodes[b].childnum == n;
}

int main() {
  int dist,q,a,b,cost = 0;
  scanf("%d",&n);
  for (int i = 1;i <= n;i++) {
    nodes[i].father = i;
    nodes[i].childnum = 1;
    for (int j = 1;j <= n;j++) {
      scanf("%d",&dist);
      if (i < j) {
        edges[edge_num].a = i;
        edges[edge_num].b = j;
        edges[edge_num].dist = dist;
        edge_num ++;
      }
    }
  }
  scanf("%d",&q);
  for (int i = 0;i < q;i++) {
    scanf("%d%d",&a,&b);
    if (merge(a,b)) {
      printf("0\n");
      return 0;
    }
  }
  sort(edges, edges+edge_num,cmp);
  for (int i = 0;i < edge_num;i++) {
    a = get_father(edges[i].a);
    b = get_father(edges[i].b);
    if (a == b) {
      continue;
    }
    cost += edges[i].dist;
    if (merge(a,b)) {
      printf("%d\n",cost);
      return 0;
    }
  }
  printf("0\n");
  return 0;
}

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

double dist[11][11];

int main() {
  int T;
  scanf("%d",&T);
  while(T--) {
    int n;
    scanf("%d",&n);
    int x[11],y[11];
    int permu[11];
    for(int i = 0;i < n;i++) {
      scanf("%d%d",&x[i],&y[i]);
      permu[i] = i;
    }
    for(int i = 0;i < n;i++) {
      for(int j = i+1;j < n;j++) {
        dist[i][j] = dist[j][i] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
      }
    }
    double min_length = 1000000.0;
    do {
      double length = 0;
      for(int i = 0;i < n-1;i++) {
        length += dist[permu[i]][permu[i+1]];
      }
      length += dist[permu[n-1]][permu[0]];
      if(min_length > length) {
        min_length = length;
      }
    } while(next_permutation(permu,permu+n));
    printf("%.2f\n",min_length);
  }
}

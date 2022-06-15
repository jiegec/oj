#include <string>

using namespace std;

#define MOD 1000000007
#define INV_2 500000004LL

long long N, M, T, A, V_MAX;
struct rst {
  int time;
  int l;
  int r;
} R[200010];

bool cmp(const struct rst &a, const struct rst &b) { return a.time < b.time; }

int main() {
  int K;
  scanf("%d", &K);
  while (K--) {
    scanf("%lld%lld%lld%lld%lld", &N, &M, &T, &A, &V_MAX);
    long long MAX_S = V_MAX / A;
    // vector<int> rst_t[200010];
    for (int i = 0; i < M; i++) {
      scanf("%d%d%d", &R[i].time, &R[i].l, &R[i].r);
    }
    sort(R, R + M, cmp);
    /*
    for (int i = 0;i < M;i++) {
      for (int j = R[i].l;j <= R[i].r;j++) {
        rst_t[j].push_back(R[i].time);
      }
    }
     */
    long long dis = 0;
    for (int i = 0; i < N; i++) {
      int pre = 0;
      for (int j = 0; j < M; j++) {
        if (R[j].l <= i && i <= R[j].r) {
          int t = R[j].time;
          if (t - pre >= MAX_S) {
            dis += A * (MAX_S + 1) * MAX_S * INV_2;
            dis %= MOD;
            dis += (t - pre - MAX_S) * V_MAX;
            dis %= MOD;
          } else {
            dis += A * (t - pre) * (t - pre + 1) * INV_2;
            dis %= MOD;
          }
          pre = t;
        }
      }
      if (T - pre >= MAX_S) {
        dis += A * (MAX_S + 1) * MAX_S * INV_2;
        dis %= MOD;
        dis += (T - pre - MAX_S) * V_MAX;
        dis %= MOD;
      } else {
        dis += A * (T - pre) * (T - pre + 1) * INV_2;
        dis %= MOD;
      }
    }
    printf("%lld\n", dis);
  }
}

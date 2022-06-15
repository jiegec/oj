// http://acm.hdu.edu.cn/showproblem.php?pid=3591
#include "stdio.h"
void bag01(int cost, int value, int money, int dp[]) {
  for (int i = money; i >= cost; i--) {
    // if(dp[i] < dp[i-cost]+value) {
    if (dp[i] > dp[i - cost] + value) {
      dp[i] = dp[i - cost] + value;
    }
  }
}

void complete(int cost, int value, int money, int dp[]) {
  for (int i = cost; i <= money; i++) {
    // if(dp[i] < dp[i-cost]+value) {
    if (dp[i] > dp[i - cost] + value) {
      dp[i] = dp[i - cost] + value;
    }
  }
}

void multiply(int cost, int value, int amount, int money, int dp[]) {
  if (cost * amount >= money)
    complete(cost, value, money, dp);
  else {
    int k = 1;
    while (k < amount) {
      bag01(k * cost, k * value, money, dp);
      amount -= k;
      k += k;
    }
    bag01(cost * amount, value * amount, money, dp);
  }
}

int main() {
  int infinite = 0x4000000;
  int n, t, index = 0;
  while (scanf("%d%d", &n, &t) != EOF) {
    int dp[100860] = {0};
    for (int i = 1; i <= 20000; i++) {
      dp[i] = infinite;
    }
    if (n == 0 && t == 0) {
      break;
    }
    int number[123], value[123];
    for (int i = 0; i < n; i++) {
      scanf("%d", &number[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &value[i]);
    }
    for (int i = 0; i < n; i++) {
      multiply(number[i], 1, value[i], 20000, dp);
    }
    int ans = infinite;
    for (int i = t; i <= 20000; i++) {
      if (dp[i] + dp[i - t] < ans) {
        ans = dp[i] + dp[i - t];
      }
    }
    if (ans == infinite) {
      printf("Case %d: -1\n", ++index);
    } else {
      printf("Case %d: %d\n", ++index, ans);
    }
  }
}

#include <stdio.h>
#include <string.h>
int max(int a, int b) {
	return a > b ? a : b;
}
int dp[100][100860];
void bag01(int cost, int value, int money, int dp[]) {
	for(int i = money;i >= cost;i--) {
		if(dp[i] < dp[i-cost]+value) {
			dp[i] = dp[i-cost]+value;
		}
		
	}
}
int main() {
	int boxes, money;
	while(scanf("%d%d", &boxes, &money) != EOF) {
		memset(dp,0,sizeof(dp));
		for(int i = 1;i <= boxes;i++) {
			int cost, num;
			scanf("%d%d", &cost, &num);
			for(int j = 0;j < cost;j++) {
				dp[i][j] = -98999999;
			}
			for(int j = cost;j <= money;j++) {
				dp[i][j] = dp[i-1][j-cost];
			}
			for(int j = 0;j < num;j++) {
				int price, value;
				scanf("%d%d", &price, &value);
				bag01(price, value, money, dp[i]);
			}
			for(int j = 0;j <= money;j++) {
				dp[i][j] = max(dp[i][j], dp[i-1][j]);
			}
		}
		printf("%d\n",dp[boxes][money]);
	}
}

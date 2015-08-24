#include <stdio.h>

int max2(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int c;
	scanf("%d", &c);
	while(c--) {
		int n;
		scanf("%d",&n);
		int map[123][123],dp[123][123];
		for(int i = 1; i <= n;i++) {
			for(int j = 1;j <= i;j++) {
				scanf("%d", &map[i][j]);
				dp[i][j] = map[i][j];
			}
		}
		for(int i = n-1;i >= 1;i--) {
			for(int j = 1;j <= i;j++) {
				dp[i][j] = map[i][j] + max2(dp[i+1][j],dp[i+1][j+1]);
			}
		}
		printf("%d\n",dp[1][1]);
	}
}

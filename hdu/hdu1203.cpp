#include <stdio.h>
void bag01(int cost, double value, int money, double dp[]) {
	for(int i = money;i >= cost;i--) {
		if(dp[i] > dp[i-cost]*(1-value)) {
			dp[i] = dp[i-cost]*(1-value);
		}
		
	}
}
double dp[100860];
int main() {
	int n, m;
	while(scanf("%d%d",&n,&m),n||m) {
		for(int i = 0;i <= n;i++) {
			dp[i] = 1;
		}
		for(int i = 0;i < m;i++) {
			double b;
			int a;
			scanf("%d %lf",&a, &b);
			bag01(a,b,n,dp);
		}
		printf("%.1lf%%\n",(1-dp[n])*100);
	}
}

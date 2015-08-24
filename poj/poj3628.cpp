#include <stdio.h>
#include <string.h>
void bag01(int cost, int value, int money, int dp[]) {
	for(int i = money;i >= cost;i--) {
		if(dp[i] < dp[i-cost]+value) {
			dp[i] = dp[i-cost]+value;
		}
		
	}
}
int dp[10086000];

int main() {
	int n,b;
	while(scanf("%d%d",&n,&b)!=EOF){  
		int h[20],sum = 0;
		memset(dp,0,sizeof(dp));
		for(int i = 0;i < n;i++) {
			scanf("%d", &h[i]);
			sum += h[i];
		}
		for(int i = 0;i < n;i++) {
			bag01(h[i],h[i],sum,dp);
		}
		printf("%d\n",sum-b-dp[sum-b]);
	}
}

#include <stdio.h>
void bag01(int cost, int value, int money, int dp[]) {
	for(int i = money;i >= cost;i--) {
		if(dp[i] < dp[i-cost]+value) {
			dp[i] = dp[i-cost]+value;
		}
		
	}
}

void complete(int cost, int value, int money, int dp[]) {
	for(int i = cost;i <= money;i++) {
		if(dp[i] < dp[i-cost]+value) {
			dp[i] = dp[i-cost]+value;
		}
		
	}
}

void multiply(int cost,int value,int amount, int money, int dp[])
{
	if(cost*amount>=money)
		complete(cost,value, money, dp);
	else{
		int k=1;
		while(k<amount){
			bag01(k*cost,k*value, money, dp);
			amount-=k;
			k+=k;
		}
		bag01(cost*amount,value*amount, money, dp);
	}
}

int main() {
	int n, price[110], number[110];
	while(scanf("%d", &n), n >= 0) {
		int dp[100860] = {0};
		int sum = 0;
		for(int i = 0;i < n;i++) {
			scanf("%d%d", &price[i], &number[i]);
			sum += price[i] * number[i];
		}
		int avg = sum / 2;
		for(int i = 0;i < n;i++) {
			multiply(price[i],price[i],number[i],avg,dp);
		}
		printf("%d %d\n", sum - dp[avg], dp[avg]);
	}
}

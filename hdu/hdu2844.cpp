#include <stdio.h>
#include <string.h>
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
	int n,m;
	while(scanf("%d%d",&n,&m) != EOF) {
		if(n ==0 && m == 0) {
			break;
		}
		int a[100860],c[10086];
		for(int i = 1;i <= n;i++) {
			scanf("%d",&a[i]);
		}
		for(int i = 1;i <= n;i++) {
			scanf("%d",&c[i]);
		}
		int dp[100860];
		memset(dp,-9999999,sizeof(dp));
		dp[0] = 0;
		for(int i = 1;i <= n;i++) {
			multiply(a[i],a[i],c[i], m, dp);
		}
		int num = 0;
		for(int i = 1;i <= m;i++) {
			if(dp[i]  == i) {
				num++;
			}
		}
		printf("%d\n", num);
	}
}


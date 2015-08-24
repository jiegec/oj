#include "stdio.h"
#include <string.h>
int prices[] = {1,5,10,25};
#include <stdio.h>
int pre[100860];
int number[100860];
void bag01(int cost, int value, int money, int dp[]) {
	for(int i = money;i >= cost;i--) {
		if(dp[i-cost] != -1 && dp[i] < dp[i-cost]+value) {
			dp[i] = dp[i-cost]+value;
			pre[i] = i-cost;
			number[i] = value;
		}
		
	}
}

void complete(int cost, int value, int money, int dp[]) {
	for(int i = cost;i <= money;i++) {
		if(dp[i-cost] != -1 && dp[i] < dp[i-cost]+value) {
			dp[i] = dp[i-cost]+value;
			pre[i] = i-cost;
			number[i] = value;
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
	
	int num[4], p;
	while(scanf("%d%d%d%d%d",&p,&num[0],&num[1],&num[2],&num[3]) != EOF) {
		if(p+num[0]+num[1]+num[2]+num[3] == 0) {
			break;
		}
		int dp[100860];
		memset(dp,-1,sizeof(dp));
		dp[0] = 0;
		for(int i = 0;i < 4;i++) {
			multiply(prices[i],1,num[i], p, dp);
		}
		if(dp[p] == -1) {
			printf("Charlie cannot buy coffee.\n");
		}else {
			int ans[4] = {0};
            for(int i=p;i!=0;i=pre[i])
            {
                int k = (i-pre[i])/number[i];
                for(int j=0;j<4;j++)
                    if(k==prices[j])ans[j]+=number[i];
            }
            printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n",ans[0],ans[1],ans[2],ans[3]);
		}		
	}
} 

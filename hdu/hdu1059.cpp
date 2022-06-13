// http://acm.hdu.edu.cn/showproblem.php?pid=1059
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
	int items[6];
	int index = 0;
	while(scanf("%d%d%d%d%d%d", &items[0], &items[1],&items[2],&items[3],&items[4],&items[5]) != EOF) {
		if(items[0] + items[1] + items[2] + items[3] + items[4] + items[5] == 0) {
			break;
		}
		int sum = items[0]*1 + items[1]*2 + items[2]*3 + items[3]*4 + items[4]*5 + items[5]*6;
		if(sum%2) {  
			printf("Collection #%d:\nCan't be divided.\n\n",++index);  
			continue;  
		}  
		int avg = sum / 2;
		int dp[123456] = {0};
		for(int i = 0;i < 6;i++) {
			multiply(i+1,i+1,items[i],avg,dp);
		}
		printf("Collection #%d:\n", ++index);
		if(dp[avg] == avg) {
			printf("Can be divided.\n\n");
		}else {
			printf("Can't be divided.\n\n");
		}
	}
}

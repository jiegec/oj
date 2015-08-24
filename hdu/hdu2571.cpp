#include <stdio.h>
int max2(int a, int b) {
	return a > b ? a : b;
}

int max3(int a, int b, int c) {
	return max2(a,max2(b,c));
}

void print(int dp[21][1001], int n, int m) {
	for(int i = 0;i <= n;i++) {
		for(int j = 0;j <= m;j++) {
			printf("%-6d ",dp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

int main() {
	int c;
	scanf("%d",&c);
	while(c--) {
		int n,m;
		scanf("%d%d",&n,&m);
		int numbers[25][1005],dp[25][1005];
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {
				scanf("%d",&numbers[i][j]);
			}
		}
		for(int i = 0;i <= n;i++) {
			dp[i][0] = -99999;
		}
		for(int i = 0;i <= m;i++) {
			dp[0][i] = -99999;
		}
		dp[1][1] = numbers[1][1];
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {				 
				dp[i][j] = 0;
				dp[i][j] = max3(dp[i][j],dp[i-1][j],dp[i][j-1]);
				for(int k = 1;k < j;k++) {
					if(j % k == 0) {
						dp[i][j] = max2(dp[i][j],dp[i][k]);
					}
				}
				dp[i][j] += numbers[i][j];
				//print(dp,n,m);
			}
		}
		printf("%d\n",dp[n][m]);
	}
}

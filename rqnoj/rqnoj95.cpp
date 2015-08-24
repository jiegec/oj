#include "stdio.h"
#include "string.h"
int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int min = -9999999;
	int n, m, l, dp[100][1000];
	memset(dp,min,sizeof(dp));
	
	scanf("%d%d%d", &n, &m, &l);
	for(int i = 0;i <= l;i++) {
		dp[i][0] = 0;
	}
	for(int i = 0;i < n;i++) {
		int time, score;
		scanf("%d%d", &time, &score);
		for(int j = l;j >= time;j--) {
			for(int k = m;k >= 1;k++) {
				if(dp[j-time][k-1] != min) {
					dp[j][k] = max(dp[j-time][k-1]+score, dp[j][k]);
				}
			}
		}
	}
	if(dp[l][m] == min) {
		printf("0\n");
	}else {
		printf("%d\n", dp[l][m]);
	}
}

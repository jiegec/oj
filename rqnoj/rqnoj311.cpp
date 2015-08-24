#include <stdio.h>
#include <string.h>

int max(int a, int b) {
	return a > b ? a : b;
}
int main() {
	int n,k;
	scanf("%d%d", &n, &k);
	char s[100];
	long long num[100],number[50][50],dp[50][50];
	memset(dp,0,sizeof(dp));
	scanf("%s",s);
	for(int i = 0;i < n;i++)  {
		char c = s[i];
		num[i] = c - '0';
		for(int j = i;j < n;j++) {
			number[i][j] = num[i];
		}
		
		for(int j = 0;j < i;j++) {
			for(int k = i;k < n;k++) {
				number[j][k] *= 10;	
				number[j][k] += num[i];	
			}							
		}
	}
	for(int i = 0;i < n;i++) {
		dp[i][0] = number[0][i];
	}
	for(int i = 0;i < n;i++) {
		for(int j = 1;j <= k;j++) {
			for(int k = 0;k < i;k++) {
				dp[i][j] = max(dp[k][j-1]*number[k+1][i],dp[i][j]);
			}
		}
	}
	printf("%d\n",dp[n-1][k]);
}

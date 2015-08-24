#include <string.h>
#include <stdio.h>
int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int n,dp[10086],number[10086];
	while(scanf("%d",&n), n) {
		memset(dp,0,sizeof(dp));
		int ans = 0;
		for(int i = 1;i <= n;i++) {
			scanf("%d",&number[i]);
			dp[i] = number[i];
			for(int j = 1;j < i;j++) {
				if(number[j] < number[i]) {
					dp[i] = max(dp[i],dp[j]+number[i]);
				}				
			}
		}
		for(int i = 1;i <= n;i++) {
			ans = max(ans, dp[i]);
		}
		printf("%d\n",ans);
	} 
}

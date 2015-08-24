#include <stdio.h>
#include <memory.h>

bool prime[20];

int n;
bool visit[20];
int number[20];
void print() {	
	for(int i = 1;i < n;i++) {
		printf("%d ",number[i]);
	}
	printf("%d",number[n]);
	printf("\n");	
}
void dfs(int num) {
	if(num == n) {
		for(int i = 1;i <= n;i++) {
			if(!visit[i]) {
				number[n] = i;
				if(prime[number[n-1] + number[n]] && prime[number[n] + 1]) {
					print();
				}
				break;
			}
		}
		return ;
	}
	for(int i = 1;i <= n;i++) {
		if(!visit[i] && prime[number[num-1] + i]) {
			visit[i] = true;
			number[num] = i;
			dfs(num+1);
			visit[i] = false;
		}
	}
}
int main() {
	int i = 1;
	memset(prime,0,sizeof(prime));
	prime[2] = prime[3] = prime[5] = prime[7] = prime[11] = prime[13] = prime[17] = prime[19]
= prime[23] = prime[29] = prime[31] = prime[37] = 1 ;
	while(~scanf("%d",&n)) {
		memset(visit,0,sizeof(visit));
		number[1] = 1;
		visit[1] = true;
		printf("Case %d:\n",i);
		if(n % 2 == 0)
			dfs(2);		
		printf("\n");
		i++;
	}
}

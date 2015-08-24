#include <stdio.h>

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int e,f,n,ff[200000];
		scanf("%d %d %d", &e, &f, &n);
		ff[0] = 0;
		for(int i = 1;i <= f - e;i++) {
			ff[i] = 99999999;
		}
		for(int i = 0;i < n;i++) {
			int p,w;
			scanf("%d %d", &p, &w);
			for(int j = w;j <= f - e;j++) {
				if(ff[j] < ff[j - w] + p) {
					ff[j] = ff[j - w] + p;
				}
			}
		}
		if(ff[f - e] == 99999999) {
			printf("This is impossible.\n");
		}else {
			printf("The minimum amount of money in the piggy-bank is %d.\n",ff[f - e]);     
		}
	}
}

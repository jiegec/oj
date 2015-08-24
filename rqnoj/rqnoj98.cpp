#include <stdio.h>

int main() {
	int n,v,ff[100000] = {0},ww[100000],ss[100000],a;
	scanf("%d %d", &n, &v);
	a = 0;
	for(int c = 0;c < n;c++) {
		int m,w,s;
		scanf("%d %d %d", &m, &w, &s);
		int temp = m;
		int mul = 1;
		while(temp - mul > 0) {
    		ww[a] = w * mul;
			ss[a] = s * mul;
			a++;
			temp = temp - mul;
			mul *= 2;
		}
		if(temp != 0) {
			ww[a] = temp * w;
			ss[a] = temp * s;
			a++;
		}
	}
	for(int i = 0;i < a;i++) {
		for(int j = v;j >= ww[i];j--) {
			if(ff[j] < ff[j - ww[i]] + ss[i]) {
				ff[j] = ff[j - ww[i]] + ss[i];
			}
		}
	}
	int k = 0;
	for(int i=0;i<=v;i++)
	    if(k<ff[i])
		    k=ff[i];
	printf("%d", k);
}

#include <stdio.h>
double max(double a, double b) {
	return a > b ? a : b;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		double p;
		int n,m[10000] = {0};
		double f[10000] = {0.0}, pj[10000] = {0};
		int sum = 0;
		scanf("%lf %d", &p, &n);
		for(int i = 1;i <= n;i++) {
			scanf("%d %lf", &m[i], &pj[i]);
			sum += m[i];
		}
		f[0] = 1;
		for(int i = 1;i <= n; i++) {
			for(int j = sum;j >= m[i];j--) {
				f[j] = max(f[j], f[j-m[i]] * (1-pj[i]));
			}
		}
		for(int i=sum;i >= 0;i--)
	        if(f[i] >= 1-p){
	            printf("%d\n",i);
	            break;
	        }
	}
}

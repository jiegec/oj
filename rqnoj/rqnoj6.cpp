#include <stdio.h>
#include <string.h>
int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int n, m,v[100],p[100],q[100],relation[100][3],f[10086];
	scanf("%d%d",&n,&m);
	n/=10;
	for(int i = 1;i <= m;i++) {
		scanf("%d%d%d", &v[i], &p[i], &q[i]);
		v[i] /= 10;
		if(q[i] != 0) {
			relation[q[i]][++relation[q[i]][0]] = i;
		}
	}
	memset(f,0,sizeof(f));
	for(int i = 1;i <= m;i++) {
		if(q[i] == 0) {
			for(int j = n;j >= v[i];j--) {
				f[j] = max(f[j],f[j-v[i]]+v[i]*p[i]);
				int a = relation[i][1];
				int b = relation[i][2];
				if(relation[i][0]>=1 && j >= v[i]+v[a]) {
					f[j] = max(f[j],f[j-v[i]-v[a]] + v[i]*p[i] + v[a]*p[a]);
				}
				if(relation[i][0]==2) {
					if(j >= v[i]+v[b]) {
						f[j] = max(f[j],f[j-v[i]-v[b]] + v[i]*p[i] + v[b]*p[b]);
					}
					if(j >= v[i]+v[a]+v[b]) {
						f[j] = max(f[j],f[j-v[i]-v[a] - v[b]] + v[i]*p[i] + v[a]*p[a] + v[b]*p[b]);
					}
				}
			}
		}		
	}
	printf("%d\n",f[n]*10);
} 

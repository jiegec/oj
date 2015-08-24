#include "stdio.h"
#include <string.h>
#define max(a,b) (a) > (b) ? (a) : (b)
int main() {
  int cash;
  while(scanf("%d", &cash) != EOF) {
  	  int N, size, n[10], d[10], f[100005] = {0}, prev[100005] = {0};
	  scanf("%d", &N);
	  for(int i = 0;i < N;i++) {
	      scanf("%d %d", &n[i], &d[i]);
	  }
	  for(int i = 0;i < N;i++) {
	      for(int j = 0;j <= cash;j++) {
	          	for(int k = 0;k <= n[i];k++) {
	          		if(j >= k*d[i]) {
	          			f[j] = max(f[j], prev[j-k*d[i]] + k*d[i]);
	          		}else {
	          			break;
	          		}
	          	}
	      }
	      memcpy(prev, f, sizeof(f));
	  }
	  printf("%d\n", f[cash]);	
  }
  
}

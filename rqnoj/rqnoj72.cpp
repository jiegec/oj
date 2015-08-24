#include <stdio.h>
#include <math.h>

int main() {
	int n;
	scanf("%d", &n);
    int m[101], sum = 0, avg;
    int f[10001] = {0};
    for(int i = 0;i < n;i++) {
    	scanf("%d", &m[i]);
        sum += m[i];
    }
    avg = sum / 2;
    for(int i = 0;i < n;i++) {
    	for(int j = avg;j >= m[i];j--) {
    		if(f[j] < f[j-m[i]] + m[i])
    		    f[j] = f[j-m[i]] + m[i];
    	}
    }
    printf("%d", sum - 2 * f[avg]);
}

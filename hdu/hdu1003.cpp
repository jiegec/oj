// http://acm.hdu.edu.cn/showproblem.php?pid=1003
#include <iostream>
#include <fstream>

using namespace std;

int main() {
	int T,N,fmax,lmax;
	int f[100001],a[100001];
	cin >> T;
	for(int i = 1;i <= T;i++) {
		cin >> N;
		for(int j = 1;j <= N;j++) {
			cin >> a[j];
		}
		f[1] = a[1];
		for(int k = 2;k <= N; k++) {
			if(f[k-1] + a[k] >= a[k]) {
				f[k] = f[k-1] + a[k];
			}else {
				f[k] = a[k];
			}
		} 
		fmax = -2147483647;
		lmax = -2147483647;
		for(int l = 1;l <= N;l++) {
			if(fmax < f[l]) {
				fmax = f[l];
				lmax = l;
			}
		}
		int sum = 0;
		int start = 0;
		
		for(int m = lmax;m >= 1;m--) {
			sum += a[m];
			if(sum == fmax) {
				start = m;
			}
		}
		cout << "Case " << i << ":" << endl;
		cout << fmax << " " << start << " " << lmax << endl;
		if(i != T) {
			cout << endl;
		}
	}
	return 0;
}

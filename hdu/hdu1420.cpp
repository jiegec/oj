// http://acm.hdu.edu.cn/showproblem.php?pid=1420
#include <iostream>
using namespace std;
long long  powmod( long long a, long long n, long long k )
{
    long long d = 1;
    for (a %= k; n > 0; n >>= 1)
    {
        if(n & 1)
            d = (d*a)%k;
        a = (a*a)%k;
    }
    return d;
}

int main() {
	long long n;
	cin >> n;
	for(long long i = 1;i <= n;i++) {
		long long a,b,c;
		cin >> a >> b >> c;
		cout << powmod(a,b,c) << endl;
	}
	return 0;
}

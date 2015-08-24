#include <iostream>
#include <stdio.h>
using namespace std;

struct position {
	int x;
	int y;
};
char ditu[101][101];
int m,n;
int ret = 0;
int a[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
void dfs(int x, int y) {
	ditu[x][y] = 0;
	for(int i = 0;i < 8;i++) {
		int tempx = x + a[i][0];
		int tempy = y + a[i][1];
		if(tempx >= 1 && tempx <= m  && tempy >= 1 && tempy <= n && ditu[tempx][tempy]) {
			dfs(tempx,tempy);
		}
	}
}

int main() {    
    char c;    
    //freopen("youtian.in","r",stdin);
    while(1) {    		 
             cin >> m >> n;
             ret = 0;
             if(m == 0)
                  break;
             for(int i = 1;i <= m;i++) {
                     for(int j = 1;j <= n;j++) {
                     	cin >> c;
                     	if(c == '*')
                     		 ditu[i][j] = 0;
                   		 else
                   		 	 ditu[i][j] = 1;
                     }
             }
             for(int i = 1;i <= m;i++) {
                     for(int j = 1;j <= n;j++) {
                     	if(ditu[i][j]) {
                     		ret++;
                     		dfs(i,j);
                     	}
                     				  
                     }
             }
             cout << ret << endl;
    }    
    return 0;
}

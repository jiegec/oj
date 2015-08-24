#include <stdio.h>
#include <memory.h>

int n,m;
int map[7][7];
int maxnum;

int direction[4][2] = {{1,0},{0,-1},{-1,0},{0,1}};

bool dfs(int x,int y, int num) {
	if(x < 1 || x > n || y < 1 || y > m) {
		return false;
	}
	if(map[x][y]) {
		return false;
	}
	num++;
	if(num == maxnum) {
		return true;
	}
	map[x][y] = 1;
	
	for(int j = 0;j < 4;j++) {
		if(dfs(x + direction[j][0],y + direction[j][1],num)) {
			map[x][y] = 0;
			return true;
		}
	}
	map[x][y] = 0;
	return false;	
}

int main() {
	while(scanf("%d %d\n", &n, &m) != EOF) {
		if(n == 0) {
			break;
		}
		maxnum = 0;
		for(int i = 1;i <= n;i++) {
			char s[256];
			gets(s);
			for(int j = 1;j <= m;j++) {
				char c = s[j - 1];
				if(c == '.') {
					map[i][j] = 0;
					maxnum++;
				}else if(c == 'S'){
					map[i][j] = 1;
				}				
			}
		}
		if(dfs(1,1,0)) {
			printf("YES\n");
		}else {
			printf("NO\n");
		}
	}
}

#include <stdio.h>

int n,m;
int map[1001][1001];
//int visit[1001][1001];
int direction[4][2] = {{1,0},{0,-1},{-1,0},{0,1}};
int x2,y2;

int abs(int x) {
	return x < 0 ? -x : x;
}
int signum(int x) {
	return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

bool dfs(int x,int y, int d, int turn) {
	if(x == x2 && y == y2) {
		return true;
	}
	if(map[x][y] != 0) {
		return false;
	}
	if(x < 1 || x > n || y < 1 || y > m) {
		return false;
	}
	if(turn > 2) {
		return false;
	}
	//if(visit[x][y]) {
	//	return false;
	//}
	
	if(turn == 2) {
		int dirx = direction[d][0];
		int diry = direction[d][1];
		if(signum(dirx) != signum(x2 - x)) {
			return false;
		}
		if(signum(diry) != signum(y2 - y)) {
			return false;
		}
	}	
		
	//visit[x][y] = true;
	for(int j = 0;j < 4;j++) {
		if(abs(d-j) != 2 && dfs(x + direction[j][0],y + direction[j][1],j,d == j ? turn : (turn + 1))) {
			//visit[x][y] = false;
			return true;
		}
	}
	//visit[x][y] = false;
	return false;
}

int main() {
	while(scanf("%d %d",&n,&m) != EOF) {
		if(n == 0) {
			break;
		}
		for(int i = 1;i <= n;i++) {
			for(int j = 1;j <= m;j++) {
				scanf("%d",&map[i][j]);
			}
		}
		int q;
		scanf("%d",&q);
		for(int i = 1;i <= q;i++) {
			int x1,y1;
			scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
			if(x1 < 1 || x1 > n || y1 < 1 || y1 > m) {
				printf("NO\n");
				continue;
			}
			if(x2 < 1 || x2 > n || y2 < 1 || y2 > m) {
				printf("NO\n");
				continue;
			}
			if(x1 == x2 && y1 == y2) {
				printf("NO\n");
				continue;
			}
			if(map[x1][y1] != map[x2][y2]) {
				printf("NO\n");
				continue;
			}
			if(map[x1][y1] == 0 || map[x2][y2] == 0) {
				printf("NO\n");
				continue;
			}
			//memset(visit,0,sizeof(visit));
			//visit[x1][y1] = true;
			bool flag = true;
			for(int j = 0;j < 4 && flag;j++) {
				if(dfs(x1 + direction[j][0],y1 + direction[j][1],j,0)) {
					printf("YES\n");
					flag = false;
				}
			}
			if(flag) {
				printf("NO\n");
			}
			//visit[x1][y1] = false;
		}
	}
	return 0;
}

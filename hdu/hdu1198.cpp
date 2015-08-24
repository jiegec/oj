#include <iostream>
using namespace std;
int m,n;
struct farm {
	int up;
	int right;
	int down;
	int left;
};
struct farm A = {1,0,0,1};
struct farm B = {1,1,0,0};
struct farm C = {0,0,1,1};
struct farm D = {0,1,1,0};
struct farm E = {1,0,1,0};
struct farm F = {0,1,0,1};
struct farm G = {1,1,0,1};
struct farm H = {1,0,1,1};
struct farm I = {0,1,1,1};
struct farm J = {1,1,1,0};
struct farm K = {1,1,1,1};
struct farm* states[51][51];
bool used[51][51];

void dfs(int x, int y) {
	used[x][y] = true;
	if(states[x][y]->up) {
		int tempx = x - 1;
		int tempy = y;
		if(tempx >= 1 && tempx <= m  && tempy >= 1 && tempy <= n && !used[tempx][tempy] && states[tempx][tempy]->down) {
			dfs(tempx,tempy);
		}
	}
	if(states[x][y]->right) {
		int tempx = x;
		int tempy = y + 1;
		if(tempx >= 1 && tempx <= m  && tempy >= 1 && tempy <= n && !used[tempx][tempy] && states[tempx][tempy]->left) {
			dfs(tempx,tempy);
		}
	}
	if(states[x][y]->down) {
		int tempx = x + 1;
		int tempy = y;
		if(tempx >= 1 && tempx <= m  && tempy >= 1 && tempy <= n && !used[tempx][tempy] && states[tempx][tempy]->up) {
			dfs(tempx,tempy);
		}
	}
	if(states[x][y]->left) {
		int tempx = x;
		int tempy = y - 1;
		if(tempx >= 1 && tempx <= m  && tempy >= 1 && tempy <= n && !used[tempx][tempy] && states[tempx][tempy]->right) {
			dfs(tempx,tempy);
		}
	}
}
int main() {
	while(1) {
		cin >> m >> n;
		if(m < 0 || n < 0) {
			break;
		}
		for(int i = 1;i <= m;i++) {
			for(int j = 1;j <= n;j++) {
				used[i][j] = false;
				char ch;
				cin >> ch;
				if(ch == 'A'){
					states[i][j] = &A;
				}else if(ch == 'B') {
					states[i][j] = &B;
				}else if(ch == 'C') {
					states[i][j] = &C;
				}else if(ch == 'D') {
					states[i][j] = &D;
				}else if(ch == 'E') {
					states[i][j] = &E;
				}else if(ch == 'F') {
					states[i][j] = &F;
				}else if(ch == 'G') {
					states[i][j] = &G;
				}else if(ch == 'H') {
					states[i][j] = &H;
				}else if(ch == 'I') {
					states[i][j] = &I;
				}else if(ch == 'J') {
					states[i][j] = &J;
				}else if(ch == 'K') {
					states[i][j] = &K;
				}
			}
		}
		int count = 0;
		for(int i = 1;i <= m;i++) {
			for(int j = 1;j <= n;j++) {
				if(!used[i][j]) {
					count++;
					dfs(i,j);
				}
			}
		}
		cout << count << endl;
	}
	return 0;
}

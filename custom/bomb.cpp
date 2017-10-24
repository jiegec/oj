#include <stdio.h>
#include <string.h>

char map[16][11];
char oldmap[16][11];
int bombx[5];
int bomby[5];
int n,r,c;

#define W 0
#define N 1
#define E 2
#define S 3
#define NW 4
#define NE 5
#define SW 6
#define SE 7
int d[8][2] = {{0,-1},{-1,0},{0,1},{1,0},
               {-1,-1},{-1,1},{1,-1},{1,1}};

bool dfs3(int x, int y, int dir) {
  if(0 > x || x >= r || 0 > y || y >= c)
    return true;
  if(map[x][y] == 'D')
    return false;
  if(map[x][y] == '#')
    return true;
  switch(map[x][y]) {
    case '*':
      map[x][y] = '-';
      if(dir < 4) {
        return dfs3(x+d[dir][0],y+d[dir][1],dir);
      } else {
        if(dir == NW) {
          return dfs3(x+d[N][0],y+d[N][1],N) && dfs3(x+d[W][0],y+d[W][1],W) && dfs3(x+d[NW][0],y+d[NW][1],NW);
        } else if (dir == NE) {
          return dfs3(x+d[N][0],y+d[N][1],N) && dfs3(x+d[E][0],y+d[E][1],E) && dfs3(x+d[NE][0],y+d[NE][1],NE);
        } else if (dir == SE) {
          return dfs3(x+d[S][0],y+d[S][1],S) && dfs3(x+d[E][0],y+d[E][1],E) && dfs3(x+d[SE][0],y+d[SE][1],SE);
        } else if (dir == SW) {
          return dfs3(x+d[S][0],y+d[S][1],S) && dfs3(x+d[W][0],y+d[W][1],W) && dfs3(x+d[SW][0],y+d[SW][1],SW);
        }
      }
    case 'W':
      map[x][y] = '-';
      return dfs3(x+d[W][0],y+d[W][1],W);
    case 'N':
      map[x][y] = '-';
      return dfs3(x+d[N][0],y+d[N][1],N);
    case 'E':
      map[x][y] = '-';
      return dfs3(x+d[E][0],y+d[E][1],E);
    case 'S':
      map[x][y] = '-';
      return dfs3(x+d[S][0],y+d[S][1],S);
  }
}

bool dfs2(int x, int y) {
  int i;
  switch(map[x][y]) {
    case 'D':
      return false;
    case '#':
      return true;
    case '*':
      for(i = 0;i < 8;i++) {
          if(!dfs3(x,y,i)) {
            return false;
          }
      }return true;
    case 'W':
      return dfs3(x,y,W);
    case 'N':
      return dfs3(x,y,N);
    case 'S':
      return dfs3(x,y,S);
    case 'E':
      return dfs3(x,y,E);
  }
}

bool dfs(int bomb,int x,int y) {
  if(bomb == n) {
    for(int i = 0;i < r;i++) {
      for(int j = 0;j < c;j++) {
        if(map[i][j] == '*' || map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'E'
          || map[i][j] == 'S')
          return false;
      }
    }
    bombx[bomb] = x;
    bomby[bomb] = y;
    return true;
  }
  while(1) {
    y++;
    if(y == c) {
      y = 0;
      x++;
      if(x == r) {
        return false;
      }
    }
    if(map[x][y] == 'D' || map[x][y] == '#') {
      continue;
    }
    memcpy(oldmap,map,sizeof(map));
    if(dfs2(x,y)) {
      if(dfs(bomb+1,x,y)) {
        bombx[bomb] = x;
        bomby[bomb] = y;
        return true;
      }
    }
    memcpy(map,oldmap,sizeof(map));
  }
}

int main() {
  int T;
  scanf("%d",&T);
  while(T--) {
    scanf("%d%d%d\n",&n,&r,&c);
    for(int i = 0;i < r;i++) {
      for(int j = 0;j < c;j++) {
        scanf("%c",&map[i][j]);
      }
      scanf("\n");
    }
    if(dfs(0,0,-1)) {
      printf("YES\n");
      for(int i = 0;i < n;i++) {
        printf("%d %d\n",bombx[i]+1,bomby[i]+1);
      }
    } else {
      printf("NO\n");
    }
  }
}

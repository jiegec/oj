// http://acm.hdu.edu.cn/showproblem.php?pid=1667
#include <cstdio>
int bound;
bool flag;
int rot[8][7]={{22,20,15,11,6,2,0}, // A
               {23,21,17,12,8,3,1}, // B
               {4,5,6,7,8,9,10}, // C
               {13,14,15,16,17,18,19}, // D,
               {1,3,8,12,17,21,23}, // E
               {0,2,6,11,15,20,22}, // F
               {19,18,17,16,15,14,13}, // G
               {10,9,8,7,6,5,4} // H
  };
int mid[8]={6,7,8,11,12,15,16,17};
int p[127];

inline int max(int a,int b){
  return a>b?a:b;
}

struct D{
    int a[24];
    int H() {
      int n[4]={0};
      for(int i = 0;i < 8;i++) {
        n[a[mid[i]]]++;
      }
      return 8-max(max(n[1],n[2]),n[3]);
    }
}s;

void rotate(int dir) {
  int temp = s.a[rot[dir][6]];
  for(int i=5;i>=0;i--) {
    s.a[rot[dir][i+1]] = s.a[rot[dir][i]];
  }
  s.a[rot[dir][0]] = temp;
}

#define inc(dir,rev) {rotate(dir);tmp=dfs(x+1,dir);if(flag)return p[x]=(dir),tmp;if(nxt>tmp)nxt=tmp;rotate(rev);}

int dfs(int x,int las){
  int hv = s.H();
  if(x+hv>bound)
    return x+hv;
  if(hv == 0)
    return flag=true,x;
  int nxt=0x7FFF,tmp;
  if(las!=5) inc(0,5);
  if(las!=4) inc(1,4);
  if(las!=7) inc(2,7);
  if(las!=6) inc(3,6);
  if(las!=1) inc(4,1);
  if(las!=0) inc(5,0);
  if(las!=3) inc(6,3);
  if(las!=2) inc(7,2);
  return nxt;
}

int main() {
  while(1){
    flag=false;
    scanf("%d",&s.a[0]);
    if(!s.a[0])
      break;
    for(int i = 1;i < 24;i++) {
      scanf("%d",&s.a[i]);
    }
    for(bound=s.H();!flag;bound=dfs(0,-1));
    if(bound == 0){
      printf("No moves needed\n");
    } else {
      for(int i=0;i<bound;i++)
        putchar('A'+p[i]);
      putchar('\n');
    };
    printf("%d\n",s.a[mid[0]]);
  }
}

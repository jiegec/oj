// http://acm.hdu.edu.cn/showproblem.php?pid=1560
#include <cstdio>
#include <cstring>

int bound;
bool flag;
char ch[4]={'A','C','G','T'};
int map[128];

inline int min(int a,int b){
  return a>b?b:a;
}

inline int max(int a,int b){
  return a>b?a:b;
}

struct D{
    int k;
    char s[10][10];
    int cur[10];
    int len[10];
    int H() {
      int n[4]={0};
      for(int i=0;i<k;i++){
        int tmp[4]={0};
        for(int j=cur[i];j<len[i];j++){
          tmp[map[s[i][j]]]++;
        }
        n[0]=max(n[0],tmp[0]);
        n[1]=max(n[1],tmp[1]);
        n[2]=max(n[2],tmp[2]);
        n[3]=max(n[3],tmp[3]);
      }
      return n[0]+n[1]+n[2]+n[3];
    }
}s;

int dfs(int x){
  int hv=s.H();
  if(x+hv>bound)
    return x+hv;
  if(hv==0)
    return flag=true,x;
  int nxt=0x7FFF,tmp;
  int old[10];
  memcpy(old, s.cur, sizeof(old));
  for(int i=0;i<4;i++){
    bool flag2=false;
    for(int j=0;j<s.k;j++){
      if(s.s[j][s.cur[j]]==ch[i]) {
        s.cur[j]++;
        flag2=true;
      }
    }
    if(!flag2)
      continue;
    tmp = dfs(x+1);
    if(flag)
      return tmp;
    if(nxt>tmp)
      nxt=tmp;
    memcpy(s.cur,old,sizeof(old));
  }
  return nxt;
}

int main() {
  map['A']=0;
  map['C']=1;
  map['G']=2;
  map['T']=3;
  int N;
  scanf("%d",&N);
  while(N--){
    flag=false;
    scanf("%d",&s.k);
    for(int i=0;i<s.k;i++){
      scanf("%s",s.s[i]);
      s.cur[i]=0;
      s.len[i]=strlen(s.s[i]);
    }
    for(bound=s.H();!flag;bound=dfs(0));
    printf("%d\n",bound);
  }
}

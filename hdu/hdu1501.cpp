// http://acm.hdu.edu.cn/showproblem.php?pid=1501
#include <cstdio>
#include <cstdlib>
#include <cstring>

char first[210],second[210],third[210];
bool visit[210][210];
int firstlen,secondlen,thirdlen;
bool dfs(int firstx, int secondx, int thirdx) {
  if (thirdx == thirdlen) {
    return true;
  }
  if(visit[firstx][secondx])
    return false;
  visit[firstx][secondx] = true;
  if(first[firstx]==third[thirdx]) {
    if(dfs(firstx+1,secondx,thirdx+1))
      return true;
  }
  if(second[secondx]==third[thirdx]){
    if(dfs(firstx,secondx+1,thirdx+1))
      return true;
  }
  return false;
}
int main() {
  int n;
  scanf("%d",&n);
  for(int i = 1;i <= n;i++) {
    memset(visit,0,sizeof(visit));
    scanf("%s %s %s",first,second,third);
    firstlen = strlen(first);
    thirdlen = strlen(third);
    secondlen = strlen(second);
    if(dfs(0,0,0)) {
      printf("Data set %d: yes\n",i);
    }else {
      printf("Data set %d: no\n",i);
    }
  }
}

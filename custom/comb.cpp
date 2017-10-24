#include <stdio.h>
#include <string.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

char buffer[100024];

int main() {
  int n;
  scanf("%d\n",&n);
  for (int k = 0;k < n;k++) {
    int count[10] = {0};
    int count2[10] = {0};
    scanf("%s",buffer);
    int len = strlen(buffer);
    if(len == 1) {
      if(buffer[0] == '5')
        printf("1\n");
      else
        printf("0\n");
      continue;
    }
    for(int i = 0;i < len;i++) {
      if(buffer[i] == ' ')
        continue;
      count[buffer[i] - '0']++;
      count2[buffer[i] - '0']+=2;
    }
    int num = 0,ans = 0,count0 = count[0];
    num = count0;
    for(int ii = 0;ii <= count0;ii++) {
      count[0] -= ii;
      count2[0] -= 2*ii;
      for(int i = 1;i <= 5;i++) {
        if(count[i] && count[10-i]) {
          count2[i]--;
          count2[10-i]--;
          ans = 1+ii;
          ans += MIN(count2[0],count2[9]);
          ans += MIN(count2[1],count2[8]);
          ans += MIN(count2[2],count2[7]);
          ans += MIN(count2[3],count2[6]);
          ans += MIN(count2[4],count2[5]);
          if(count2[1] == 0 && count2[2] == 0 && count2[3] == 0 && count2[4] == 0 &&
             count2[5] == 0 && count2[6] == 0 && count2[7] == 0 && count2[8] == 0 && count2[0] != 0 && count2[9] != 0) {
            count2[9] -= 2;
            ans = 1 + MIN(count2[0],count2[9]);
            count2[9] += 2;
          }
          count2[i]++;
          count2[10-i]++;
          num = MAX(num, ans);
        }
      }
      count[0] += ii;
      count2[0] += 2*ii;
    }
/*
    if(count[0]) {
      num = MAX(num,count[0]);
      for(int i = 1;i <= 5;i++) {
        if(count[i] && count[10-i]) {
          count2[i]--;
          count2[10-i]--;
          ans = count[0]+1;
          ans += MIN(count2[1],count2[8]);
          ans += MIN(count2[2],count2[7]);
          ans += MIN(count2[3],count2[6]);
          ans += MIN(count2[4],count2[5]);
          count2[i]++;
          count2[10-i]++;
          num = MAX(num, ans);
        }
      }
    }

    for(int i = 1;i <= 5;i++) {
      if(count[i] && count[10-i]) {
        count2[i]--;
        count2[10-i]--;
        ans = 1;
        ans += MIN(count2[0],count2[9]);
        ans += MIN(count2[1],count2[8]);
        ans += MIN(count2[2],count2[7]);
        ans += MIN(count2[3],count2[6]);
        ans += MIN(count2[4],count2[5]);
        if(count2[1] == 0 && count2[2] == 0 && count2[3] == 0 && count2[4] == 0 &&
          count2[5] == 0 && count2[6] == 0 && count2[7] == 0 && count2[8] == 0 && count2[0] != 0 && count2[9] != 0) {
          count2[9] -= 2;
          ans = 1 + MIN(count2[0],count2[9]);
          count2[9] += 2;
        }
        count2[i]++;
        count2[10-i]++;
        num = MAX(num, ans);
      }
    }*/

    printf("%d\n",num);
  }
}

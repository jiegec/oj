#include <stdio.h>

int main() {
  int N;
  int row[20][20] = {0};
  scanf("%d",&N);
  row[0][0] = 1;
  for (int i = 1;i <= N;i++) {
    row[i][0] = 1;
    printf("%d",row[i][0]);
    for (int j = 1;j < i;j++) {
      row[i][j] = row[i-1][j-1] + row[i-1][j];
      printf(" %d",row[i][j]);
    }
    putchar('\n');
  }
  return 0;
}

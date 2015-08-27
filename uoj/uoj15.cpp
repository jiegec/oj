#include <stdio.h>

int score[5][5] = {{0, 0, 1, 1, 0},
                   {1, 0, 0, 1, 0},
                   {0, 1, 0, 0, 1},
                   {0, 0, 1, 0, 1},
                   {1, 1, 0, 0, 0}};

int main() {
  int n, na, nb, scorea = 0, scoreb = 0;
  int a[220], b[220];
  scanf("%d%d%d",&n,&na,&nb);
  for (int i = 0;i < na;i++) {
    scanf("%d",&a[i]);
  }
  for (int i = 0;i < nb;i++) {
    scanf("%d",&b[i]);
  }
  for (int i = 0;i < n;i++) {
    scorea += score[a[i % na]][b[i % nb]];
    scoreb += score[b[i % nb]][a[i % na]];
  }
  printf("%d %d\n", scorea, scoreb);
}

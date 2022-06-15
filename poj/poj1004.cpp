// http://poj.org/problem?id=1004
#include <cstdio>

int main() {
  float temp, sum = 0.0;
  for (int i = 0; i < 12; i++) {
    scanf("%f", &temp);
    sum += temp;
  }
  printf("$%.2f\n", sum / 12);
}

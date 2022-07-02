#include <stdio.h>
#include <vector>

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    int n;
    scanf("%d", &n);
    int left = 1, right = n;
    while(left < right) {
      int mid = (left + right) / 2;
      printf("? %d %d\n", left, mid);
      fflush(stdout);

      int correct = 0;
      for (int i = left;i <= mid;i++) {
        int temp;
        scanf("%d", &temp);
        if (left <= temp && temp <= mid) {
          correct ++;
        }
      }

      if (correct % 2 == 1) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    
    printf("! %d\n", left);
    fflush(stdout);
  }
	return 0;
}
// https://leetcode-cn.com/problems/next-greater-numerically-balanced-number/
class Solution {
public:
  int nextBeautifulNumber(int n) {
    if (n == 0) {
      return 1;
    }

    int nums[11] = {};
    int occur[10] = {};
    int count = 0;
    int temp_n = n;
    for (count = 0; temp_n; count++) {
      nums[count] = temp_n % 10;
      occur[temp_n % 10]++;
      temp_n /= 10;
    }

    for (int i = n + 1;; i++) {
      if (nums[0] == 9) {
        int j = 0;
        for (j = 0; nums[j] == 9; j++) {
          occur[9]--;
          nums[j] = 0;
          occur[0]++;
        }
        occur[nums[j]]--;
        nums[j] += 1;
        occur[nums[j]]++;
      } else {
        occur[nums[0]]--;
        nums[0]++;
        occur[nums[0]]++;
      }

      bool valid = true;
      for (int j = 1; j < 10; j++) {
        if (occur[j] != 0 && occur[j] != j) {
          valid = false;
          break;
        }
      }
      for (int j = 0; j < count; j++) {
        if (nums[j] == 0) {
          valid = false;
          break;
        }
      }
      if (valid) {
        return i;
      }
    }
    return -1;
  }
};
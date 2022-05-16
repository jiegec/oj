// https://leetcode.cn/problems/total-appeal-of-a-string/
// 记忆化搜索
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

class Solution {
public:
    long long appealSum(string s) {
        long long res = 0;
        long long sum[100010] = {};
        long long prefix_sum[100010] = {};
        map<char, int> last_index;
        res = 1;
        sum[0] = 1;
        prefix_sum[0] = 1;
        last_index[s[0]] = 0;
        for (int i = 1;i < s.length();i++) {
            if (last_index.find(s[i]) == last_index.end()) {
                // new
                res += prefix_sum[i-1] + i + 1;
                for (int j = 0;j <= i;j++) {
                    sum[j]++;
                    if (j > 0) {
                        prefix_sum[j] = prefix_sum[j-1]+sum[j];
                    } else {
                        prefix_sum[j] = sum[j];
                    }
                }
            } else {
                // found old
                int last = last_index[s[i]];
                res += prefix_sum[i-1] + i - last;
                
                for (int j = last + 1;j <= i;j++) {
                    sum[j]++;
                    if (j > 0) {
                        prefix_sum[j] = prefix_sum[j-1]+sum[j];
                    } else {
                        prefix_sum[j] = sum[j];
                    }
                }
            }
            last_index[s[i]] = i;
        }
        
        return res;
    }
};
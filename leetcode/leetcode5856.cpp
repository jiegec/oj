// https://leetcode-cn.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        sort(tasks.begin(), tasks.end());
        int res = 0;
        while(tasks.size() > 0) {
            vector<int> dp;
            dp.resize(1 << tasks.size());
            dp[0] = 0;
            dp[1] = tasks[0];
            for (int i = 2;i < (1 << tasks.size());i++) {
                int j;
                for (j = 0;i >= (1 << j);j++);
                int high_bit = 1 << (j-1);
                dp[i] = dp[i ^ high_bit] + tasks[j-1];
            }
            int max_time = 0;
            int best = 0;
            for (int i = 0;i < (1 << tasks.size());i++) {
                // as large as possible
                if (dp[i] <= sessionTime && max_time <= dp[i]) {
                    max_time = dp[i];
                    best = i;
                }
            }
            
            res++;
            for (int i = tasks.size()-1;i >= 0;i--) {
                if (best & (1 << i)) {
                    tasks.erase(tasks.begin() + i);
                }
            }
        }
        return res;
    }
};
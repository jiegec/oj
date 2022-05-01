// https://leetcode-cn.com/problems/recover-the-original-array/
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        multiset<int> elements;
        multiset<int> cur_elements;
        for (int i = 0;i < nums.size();i++) {
            int num = nums[i];
            elements.insert(num);
        }
        cur_elements = elements;
        
        // match nums[0] with another
        int n = nums.size();
        int num0 = nums[0];
        
        std::vector<int> res;
        for (int i = 1;i < n;i++) {
            int numi = nums[i];
            int k2 = numi - num0;
            // even
            if (k2 % 2 != 0 || k2 == 0) {
                continue;
            }

            res.clear();
            res.reserve(n);
            int k = k2 / 2;
            while(cur_elements.size() > 0) {
                auto begin = cur_elements.begin();
                int num = *begin;
                int upper = num + k2;
                auto upper_it = cur_elements.find(upper);
                if (upper_it == cur_elements.end()) {
                    break;
                }
                
                cur_elements.erase(begin);
                cur_elements.erase(upper_it);
                
                res.push_back(num+k);
            }
            
            if (cur_elements.size() == 0) {
                return res;
            }
            cur_elements = elements;
        }
        return res;
    }
};
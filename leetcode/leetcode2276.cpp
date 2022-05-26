// https://leetcode.cn/problems/count-integers-in-intervals/
// 二叉搜索树
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

class CountIntervals {
public:
    struct Interval {
        int left;
        int right;
        
        bool operator <(const Interval &other) const {
            return left < other.left;
        }
    };
    std::set<Interval> intervals;
    int ans;
    CountIntervals() {
        ans = 0;
    }
    
    void add(int left, int right) {
        
        auto left_it = intervals.lower_bound(Interval{left, right});
        auto right_it = intervals.upper_bound(Interval{right, right});
        
        if (left_it != intervals.begin()) {
            auto it = left_it;
            it--;
            if (it->right >= left) {
                left_it = it;
            }
        }
        
        int new_left = left;
        if (left_it != intervals.end()) {
            new_left = min(new_left, left_it->left);
        }
        int new_right = right;
        if (right_it != intervals.begin()) {
            auto it = right_it;
            it--;
            new_right = max(new_right, it->right);
        }
        
        // remove items from left_index to right_index
        for (auto it = left_it;it != right_it;it++) {
            ans -= it->right - it->left + 1;
        }
        
        intervals.erase(left_it, right_it);
        
        Interval interval;
        interval.left = new_left;
        interval.right = new_right;
        ans += new_right - new_left + 1;
        intervals.insert(interval);
    }
    
    int count() {
        return ans;
    }
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
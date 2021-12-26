// https://leetcode-cn.com/problems/sequentially-ordinal-rank-tracker/
#include <string>
using namespace std;

// https://www.codenong.com/ordered-set-and-gnu-cplusplus-pbds/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<Place, null_type, less<Place>, rb_tree_tag, tree_order_statistics_node_update>

class SORTracker {
    struct Place {
        int score;
        string name;
        
        bool operator<(const Place &other) const {
            if (score != other.score) {
                return score < other.score;
            } else {
                for (int i = 0;i < name.size() && i < other.name.size();i++) {
                    if (name[i] != other.name[i]) {
                        return name[i] > other.name[i];
                    }
                }
                return name.size() > other.name.size();
            }
        }
    };
    ordered_set places;
    int get_times = 0;
public:
    SORTracker() {

    }
    
    void add(string name, int score) {
        Place new_place;
        new_place.score = score;
        new_place.name = name;
        places.insert(new_place);
    }
    
    string get() {
        get_times ++;
        return places.find_by_order(places.size()-get_times)->name;
    }
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */
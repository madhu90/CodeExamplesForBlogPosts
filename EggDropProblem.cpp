//
//  main.cpp
//  EggDropProblem
// https://leetcode.com/problems/super-egg-drop/
//  Created by Madhumitha Raghu on 5/21/21.
//

#include <iostream>
#include <unordered_map>

typedef std::pair<int, int> pair;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};


class EggDrop {
public:
    EggDrop(int e, int f)
    : nEggs(e), nFloors(f) {
        
    }
    
    int solve() {
        return drop(nFloors, nEggs);
    }
    
private:
    int drop(int n, int k) {
        if (map.find({n,k}) != map.end())
            return map[{n,k}];
        
        // 1 floor or 0 floors
        if (n == 1 || n == 0) {
            return n;
        }
        
        // 1 egg
        if (k == 1) {
            return n;
        }
        
        int min = std::numeric_limits<int>::max();
     
        // Start from floor 1 to current floor
        // Throw the egg and every floor and there are 2 possibilities:
        // a) Egg breaks and we explore the lower floors
        // b) Egg does not break and we explore the higher floors
        // At any given floor, we need to pick the worst case number of
        // trials. However, we want to minimize this across different iterations
        for (int x = 1; x <= n; ++x) {
            min = std::min(std::max(drop(x - 1, k - 1), drop(n - x, k)), min);
        }
        
        // We add 1 because exploring a floor exhausts one trial
        map[{n,k}] = min + 1;
     
        return  map[{n,k}];
    }
    
private:
    int nEggs;
    int nFloors;
    std::unordered_map<std::pair<int,int>,int,pair_hash> map;
};


int main()
{
    EggDrop obj(2, 100);
    int res = obj.solve();
    std::cout << res << std::endl;
    return 0;
}

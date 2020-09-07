/*********************************************
*     ------------------------
*     ------------------------
*     file name: 347.cpp
*     author   : @ JY
*     date     : 2020--08--18
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stdlib.h>

//347. 前 K 个高频元素
class Solution{
    public:
        std::vector<int> topKFrequent(std::vector<int>nums, int k){
            struct Cmp{
                bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b){
                    return a.second < b.second;
                }
            };
            std::unordered_map<int, int> mp;
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Cmp> q;
            std::vector<int> res;
            for(auto &n : nums)++mp[n];
            for(auto &m : mp)q.push(m);
            for(int i=0; i<k; ++i)res.push_back(q.top().first), q.pop();
            return res;
        }
};

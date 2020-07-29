/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_qujian_pro.cpp
*     author   : @ JY
*     date     : 2020--07--23
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
class Solution{
    public:
         //cc435. 无重叠区间
//给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。 注意: 可以认为区间的终点总是大于它的起点。 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。
        int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals){
            int size = intervals.size();
            if(!size)return 0;
            std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto&b){
                    return a[1] < b[1];
            });
            int c    = 1;
            int e    = intervals[0][1];
            for(int i=1; i<size; ++i){
                if(intervals[i][0] >= e){
                    ++c;
                    e = intervals[i][1];
                }
            }
            return size - c;
        }
//452
    int findMinArrowShots(std::vector<std::vector<int>>& p) {
        int size = p.size();
        if(!size)return 0;
        std::sort(p.begin(), p.end(), [](const auto& a, const auto& b){
                return 1[a] < 1[b];
        });
        int res = 1;
        int end = p[0][1];
        for(auto &n : p){
            if(n[0] > end){
                ++res;
                end = n[1];
            }
        }
        return res;
    }
//给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。 现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。 给定一个对数集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。
        int findLongestChain_better(std::vector<std::vector<int>>& p){
            int size = p.size();
            std::sort(p.begin(), p.end(), [](const auto& a, const auto& b){
                    return 1[a] < 1[b] || (1[a]==1[b] && 0[a]<0[b]);
            });
            int res = 1;
            int e   = p[0][1];
            for(auto &n : p){
                if(e < n[0]){
                    e = n[1];
                    ++res;
                }
            }
            return res;
        }
};

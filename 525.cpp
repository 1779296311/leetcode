/*********************************************
*     ------------------------
*     ------------------------
*     file name: 525.cpp
*     author   : @ JY
*     date     : 2020--07--07
**********************************************/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdlib.h>
class Solution{
    public:
//给定一个二进制数组, 找到含有相同数量的 0 和 1 的最长连续子数组（的长度）
        int findMaxLength(::std::vector<int>& nums){
            ::std::unordered_map<int, int> hp = {{0, -1}, };
            int sum = 0;
            int res = 0;
            for(int i=0; i<nums.size(); ++i){
                if(nums[i]){
                    sum += 1;
                }else{
                    sum += -1;
                }
                if(hp.count(sum)){
                    res = ::std::max(res, i-hp[sum]);
                }else{
                    hp[sum] = i;
                }
            }
            return res;
        }
};

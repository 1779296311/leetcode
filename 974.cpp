/*********************************************
*     ------------------------
*     ------------------------
*     file name: 974.cpp
*     author   : @ JY
*     date     : 2020--07--07
**********************************************/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdlib.h>
class Solution{
    public:
//给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。
        int subarrayDivByK(::std::vector<int>& nums, int k){
            int res = 0;
            int XOR = 0;
            ::std::unordered_map<int, int> hp = {{0,1}};
            for(auto &n : nums){
                res += hp[XOR=((XOR+n)%k+k)%k]++;
            }
            return res;
        }
};

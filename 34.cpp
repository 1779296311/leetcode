/*********************************************
*     ------------------------
*     ------------------------
*     file name: 34.cpp
*     author   : @ JY
*     date     : 2020--06--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>

class Solution {
public:
    ::std::vector<int> searchRange(::std::vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;
        int m;
        while(l<=r){
            m = l + ((r-l)>>1);
            if(nums[m] == target){
                break;
            }else if(nums[m] > target){
                r = m - 1;
            }else{
                l = m + 1;
            }
        }
        if(l>r)return {-1,-1};
        l = m;
        r = m;
        while(l>=0 && nums[l]==target){--l;}
        while(r<nums.size() && nums[r]==target){++r;}
        return {++l,--r};
    }
};

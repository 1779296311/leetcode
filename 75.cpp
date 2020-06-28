/*********************************************
*     ------------------------
*     ------------------------
*     file name: 75.cpp
*     author   : @ JY
*     date     : 2020--06--24
**********************************************/
#include <iostream>
#include <vector>
class Solution{
    public:
        void sortColors(::std::vector<int>& nums){
            partition(nums,1);
        }
        void partition(::std::vector<int>& nums, int f){
            int l   = -1;
            int r   = nums.size();
            int cur = 0;
            while(cur < r){
                if(f > nums[cur]){
                    ::std::swap(nums[++l],nums[cur++]);
                }else if(f < nums[cur]){
                    ::std::swap(nums[--r],nums[cur]);
                }else{
                    ++cur;
                }
            }
        }
};

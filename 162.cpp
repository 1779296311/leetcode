/*********************************************
*     ------------------------
*     ------------------------
*     file name: 162.cpp
*     author   : @ JY
*     date     : 2020--02--23
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int __size = nums.size();
        if(1 == __size){
            return 0;
        }
        int __r = __size-1;
        int __l = 0;
        int __m;
        while(__l < __r){
            __m = (__r+__l)/2;
            if(nums[__m] < nums[__m+1]){
                __l = ++__m;
            }else{
                __r = __m;
            }
        }
        return __l;
    }
};

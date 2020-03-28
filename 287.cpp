/*********************************************
*     ------------------------
*     ------------------------
*     file name: 287.cpp
*     author   : @ JY
*     date     : 2020--02--25
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int __size = nums.size();
        if(!__size){
            return 0;
        }
        int __r = nums[0];
        int __l = nums[0];

        do{
            __r = nums[__r];
            __l = nums[nums[__l]];
        }while(__r != __l);
        __r = nus[0];
        while(__r != __l){
            __r = nums[__r];
            __l = nums[__l];
        }
        return __r;
    }
};

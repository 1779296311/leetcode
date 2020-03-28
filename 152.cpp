/*********************************************
*     ------------------------
*     ------------------------
*     file name: 152.cpp
*     author   : @ JY
*     date     : 2019--09--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
using  namespace  std;
/*
给定一个整数数组nums，找出一个序列中乘积最大的连续子序列该序列至少包含一个数）。*/
class Solution{
    public:
        int maxProduct(vector<int>& nums){
            int size    = nums.size();
            int MAX     = INT_MIN;
            int now_max = 1;
            int now_min = 1;
            for(int i=0; i<size; i++){
                if(nums[i] < 0){
                    now_max = now_max ^ now_min;
                    now_min = now_max ^ now_min;
                    now_max = now_max ^ now_min;
                }
                now_max = max(now_max*nums[i], now_max);
                now_min = min(now_min*nums[i], now_min);
                MAX     = max(MAX, now_max);
            }
            return MAX;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {1,4,-5,6,-2,8,-3,20};
    cout <<te.maxProduct(nums);
    return 0;
}

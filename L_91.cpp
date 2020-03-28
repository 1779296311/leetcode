/*********************************************
*     file name: L_91.cpp
*     author   : @ JY
*     date     : 2019--09--23
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
using  namespace  std;
/*
给一个整数数组，调整每个数的大小，使得相邻的两个数的差不大于一个给定的整数target，调整每个数的代价为调整前后的差的绝对值，求调整代价之和最小是多少*/
class Solution{
    public:
        MinimumAdjustmentCost(vector<int>& nums, int target){
            int size = nums.size();
            vector<vector<int>> memo(size+1, vector<int>(100+1, INT_MAX));
            for(int i=0; i<=100; i++){
                memo[1][i] = abs(nums[0] - target);
            }
            for(int i=2; i<=size; i++){
                for(int j=1; j<=100; j++){
                    for(int k=j-target; k<=j+target; k++){
                        if(k<=0 || k>=100){
                            continue;
                        }
                        memo[i][j] = min(memo[i][j], memo[i-1][k]+abs(nums[i-1]-j));
                    }
                }
            }
            int res = INT_MAX;
            for(int i=0; i<=100; i++){
                res = min(res, memo[size][i]);
            }
            return res;
        }
};

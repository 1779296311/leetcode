/*********************************************
*     ------------------------
*     ------------------------
*     file name: L_92.cpp
*     author   : @ JY
*     date     : 2019--09--16
**********************************************//*
在n个物品中挑选若干物品装入背包，最多能装多满？假设背包的大小为m，每个物品的大小为A[i]你不可以将物品进行切割*/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int backPack(int m, vector<int>& nums){
            int size = nums.size();
            if(size == 0){
                return 0;
            }
            vector<bool> memo(m+1,0);
            for(int i=0; i<=size; i++){
                memo[i] = (nums[0] == i);
            }
            for(int i=1; i<size; i++){
                for(int j=m; j>=nums[i]; j--){
                    memo[j] = memo[j] || memo[j-nums[i]];
                }
            }
            for(int i=m; i>=0; i++){
                if(memo[i]){
                    return i;
                }
            }
            return 0;
        }
};

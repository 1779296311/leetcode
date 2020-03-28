/********************************************* 
*     ------------------------
*     file name: 416.cpp
*     author   : @ JY
*     data     : 2019--09--12
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vecotr>
using  namespace  std;

class Solution{
    public:
        bool canPartition(vector<int>& nums){
            int size = nums.size();

            int sum = 0;
            for(int num : nums){
                sum  = sum + num;
            }
            if(sum % 2 != 0){
                return false;
            }
            sum = sum / 2;
            vector<bool> memo(sum+1, 0);
            for(int i=0; i<=size; i++){
                memo[i] = (i==nums[0]);
            }
            for(int i=1; i<=size; i++){
                for(int j=sum; j>=nums[i]; j--){
                    memo[j]  = memo[j] || (memo[j-nums[i]]);
                }
            }
            return memo[sum];
        }
};

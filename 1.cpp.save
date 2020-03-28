/*********************************************
*     ------------------------
*     ------------------------
*     file name: 1.cpp
*     author   : @ JY
*     date     : 2019--09--27
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        vector<int> twoSum(vector<int>& nums, int target){
            int size = nums.size();
            vector<int> memo(2);
            for(int i=0; i<size-1; i++){
                for(int j=i+1; j<size; j++){
                    if(nums[i] + nums[j] == target){
                        memo[0] = i;
                        memo[0] = j;
                        return memo;
                    }
                }
            }
        }
};

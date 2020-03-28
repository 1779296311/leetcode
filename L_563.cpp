/*********************************************
*     file name: L_563.cpp
*     author   : @ JY
*     date     : 2019--09--16
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int maxPackV(vector<int>& nums, int target){
            int size = nums.size();
            if(size == 0){
                return 0;
            }
            vector<int> memo(target+1,0);
            memo[0] = 1;
            for(int i=0; i<size; i++){
                for(int j=target; j>=nums[i]; j--){
                    memo[j] = memo[j] + memo[j-nums[i]];
                }
            }
            return memo[target];
        }
};

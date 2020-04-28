/*********************************************
*     ------------------------
*     ------------------------
*     file name: longestIncreasingContinuousSubsequence.cpp
*     author   : @ JY    
*     data     : 2019--09--13
**********************************************/
#include <iostream>
#include <climits>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int longestIncreasingContinuousSubsequence(vector<int>& nums){
            int len  = nums.size();
            if(len == 0){
                return 0;
            }
            int max  = INT_MIN;
            vector<int> memo(len, 1);
            for(int i=1; i<len; i++){
                if(nums[i] > nums[i-1]){
                    memo[i] = memo[i-1] + 1;
                }
                if(max < memo[i]){
                    max = memo[i];
                }
            }
            for(int i=len-2; i>=0; i--){
                if(nums[i+1] > nums[i]){
                    memo[i] = memo[i-1] + 1;
                }
                if(max < memo[i]){
                    max = memo[i];
                }
            }
            return max;
        }
};
int main(int argc,const char *argv[]){
}

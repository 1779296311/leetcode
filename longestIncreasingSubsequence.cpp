/*********************************************
*     ------------------------
*     ------------------------
*     file name: longestIncreasingSubsequence.cpp
*     author   : @ JY
*     date     : 2020--03--19
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
       int longestIncreasingSubsequence(vector<int>& nums){
            int size = nums.szie();
            vector<int> dp(size,1);
            for(int i=1; i<size; ++i){
                for(int j=0; j<i; ++j){
                    if(nums[i]>nums[j]){
                        dp[i] = max(dp[i],d[j]+1);
                    }
                }
            }
            return dp[size-1];
        }
};
int main(int argc,const char *argv[]){
    <??>;
    return 0;
}

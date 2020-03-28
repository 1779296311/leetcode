/*********************************************
*     ------------------------
*     ------------------------
*     file name: 55.cpp
*     author   : @ JY
*     date     : 2020--03--15
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        int mi   = nums[0];
        int jump = 0;
        while(jump<size&&jump<=mi){
            if(mi<jump+nums[jump]){
                mi = nums[jump]+jump;
            }
            ++jump;
        }
        return jump==size;
    }
    bool canJump_dp(vector<int>& nums){
        int size = nums.szie();
        vector<bool> dp(size);
        for(int i=0; i<size; ++i){
            if(!i){
                dp[i] = true;
            }else{
                for(int j=0; j<i; ++j){
                    if(dp[i] && i-j>=nums[j]){
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        return dp[size-1];
    }
};

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 1425.cpp
*     author   : @ JY
*     date     : 2020--05--29
**********************************************/
#include <iostream>
#include <climits>
#include <queue>
#include <vector>
#include <stdlib.h>
class Solution {
public:
    int constrainedSubsetSum(::std::vector<int>& nums, int k) {
        ::std::priority_queue<::std::pair<int,int>>q;
        ::std::vector<int> dp(nums.size(),0);
        int res = INT_MIN;
        int i   = 0;
        while(i<nums.size()){
            dp[i] = nums[i];
            while(!q.empty() && q.top().second<(i-k)){q.pop();}
            dp[i] = q.empty()?dp[i]:(::std::max(dp[i], dp[i]+q.top().first));
            res   = ::std::max(dp[i],res);
            q.push(::std::make_pair(dp[i],i));
            ++i;
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<int> nums = {10,2,-10,5,20};
    te.constrainedSubsetSum(nums,2);
    return 0;
}

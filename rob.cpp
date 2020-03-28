/*********************************************
*     file name: rob.cpp
*     author   : @JY
*     data     : 2019--09--10
**********************************************/
#include "test.h"
class Solution{
    public:
        int rob(vector<int>& nums){
            int len   = nums.size();
            if(len == 0){
                return 0;
            }
            if(len == 1){
                return nums[0];
            }
            vector<int> memo(len + 1);
            memo [0] = nums[0];
            memo [1] = nums[0] > nums[1] ? nums[0] : nums[1];
            for(int i=2; i<len; i++){
                memo[i] = max(nums[i] + memo[i - 2], memo[i-1]);
            }
            return memo[len -1];
        }
        int rob_2(vector<int>& nums){
            int len   = nums.size();
            if(len == 0){
                return 0;
            }
            if(len == 1){
                return nums[0];
            }
            vector<int> memo(len + 1), memp(len + 1);
            for(int i=2; i<=len; i++){
                // nums[0]~nums[len-2]
                memp[i] = max(nums[i-2] + memp[i-2], memp[i-1]);
                // nums[1]~nums[len-1]
                memo[i] = max(nums[i-1] + memo[i-2], memo[i-1]);
            }
            for(int n : memo){
                cout <<n<<"-- ";
            }
            return max(memo[len],memp[len]);
        }

};

//int main(int argc,const char *argv[]){
//    Solution te;
//
//    vector<int> nums = {1,2,3,4,5,6,7,8};
//    te.rob(nums);
//
//    return 0;
//}


/*********************************************
*     ------------------------
*     ------------------------
*     file name: 303.cpp
*     author   : @ JY
*     date     : 2019--09--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class NumArray {
public:
    vector<int> dp;
    NumArray(vector<int>& nums) {
        int size = nums.size();
        vector<int> memo(size);
        memo[0] = nums[0];
        for(int i=1; i<size; i++){
            memo[i] = memo[i-1] + nums[i];
        }
        this->dp.swap(memo);
    }
    int sumRange(int i, int j) {
        for(int s : dp){
            cout <<s<<"-- ";
        }
        return dp[j+1] - dp[i];
    }
};
int main(int argc,const char *argv[]){
    vector<int> nums = {1,2,3,4,5,6,7};
    NumArray *te = new NumArray(nums);
    cout<<te->sumRange(2,5);
    return 0;
}

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */

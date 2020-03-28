/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: maxSubArray.cpp
*     author   : @JY    
*     data     : 2019--09--10
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using  namespace  std;

class Solution{
    public:
        int maxSubArray(vector<int>& nums){
            int len  = nums.size();

            if(len == 1){
                return nums[0];
            }
            vector<int> memo(len+1,0);

            memo[0] = nums[0];
            int max = memo[0];
            for(int i=1; i<len; i++){
                memo[i]  = (memo[i-1]>0) ? memo[i -1] + nums[i] : nums[i];
                max      = memo[i] > max ? memo[i] : max;
            }

            for(int n : memo){
                cout <<n<<endl;
            }
            return max;
        }
};

int main(int argc,const char *argv[]){

    Solution te;
    //vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    vector<int> nums = {1,2};
    cout <<te.maxSubArray(nums)<<endl;
    return 0;
}

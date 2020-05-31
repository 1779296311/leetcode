/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ61.cpp
*     author   : @ JY
*     date     : 2020--05--22
**********************************************/
#include <iostream>
#include <algorithm>
#include <climits>
#include <bitset>
#include <vector>
#include <stdlib.h>
class Solution {
public:
    bool isStraight(::std::vector<int>& nums) {
        int minV  = INT_MAX;
        int maxV  = INT_MIN;
        int zeroN = 0;
        for(int i=0; i<nums.size(); ++i){
            if(!nums[i]){
                ++zeroN;
            }else{
                minV = ::std::min(minV,nums[i]);
                maxV = ::std::max(maxV,nums[i]);
            }
        }
        if(maxV-minV>=5){
            return false;
        }
        ::std::sort(nums.begin(),nums.end());
        int tmp    = zeroN;
        int target = minV+1;
        for(int i=zeroN+1; i<nums.size(); ++i){
            if(nums[i]<target){
                return false;
            }else if(!tmp && nums[i] != target){
                return false;
            }else if(nums[i] != target){
                --i;
                --tmp;
            }
            ++target;
        }
        return true;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    ::std::vector<int>nums = {9,10,7,0,6};
    ::std::cout<<te.isStraight(nums)<<::std::endl;
    return 0;
}

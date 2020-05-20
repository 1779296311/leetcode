/*********************************************
*     ------------------------
*     ------------------------
*     file name: 153.cpp
*     author   : @ JY
*     date     : 2020--05--03
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l   = 0;
        int r   = nums.size()-1;
        int mid = 0;
        while(l<r){
            mid = l+((r-l)>>1);
            if(nums[mid]<nums[r]){
                l = mid+1 ;
            }else if(nums[mid]>nums[r]){
                r = mid;
            }else{
                return nums[l];
            }
        }
        return nums[l];
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {2,3,4,5,1,6};
    cout<<te.findMin(nums)<<endl;
    return 0;
}

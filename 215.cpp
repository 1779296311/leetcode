/*********************************************
*     ------------------------
*     ------------------------
*     file name: 215.cpp
*     author   : @ JY
*     date     : 2019--10--17
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int findKthLargest(vector<int>& nums, int k){
            if(!nums.size()){
                return 0;
            }
            int size = nums.size();
            sort(nums.begin(), nums.end());
            if(k > size){
                return nums[size-1];
            }
            return nums[k];
        }
};

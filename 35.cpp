/*********************************************
*     ------------------------
*     ------------------------
*     file name: 35.cpp
*     author   : @ JY
*     date     : 2019--09--25
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int searchInsert(vector<int>& nums, int target){
            int size = nums.size();
            if(size == 0){
                return 0;
            }
            int i=0;
            for(; i<size; i++){
                if(nums[i] >= target){
                    return i;
                }
            }
            return i;
        }

};

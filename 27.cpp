/*********************************************
*     ------------------------
*     ------------------------
*     file name: 27.cpp
*     author   : @ JY
*     date     : 2019--09--22
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int removeElement(vector<int> nums, int val){
            int size    = nums.size();
            int index   = 0;
            for(int i=0; i<size; i++){
                if(nums[i] != val){
                    nums[j] = nums[i];
                    j++;
                }
            }
            return j;
        }
};

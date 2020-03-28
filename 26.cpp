/*********************************************
*     ------------------------
*     ------------------------
*     file name: 26.cpp
*     author   : @ JY
*     date     : 2019--09--21
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        int res  = 1;
        for(int i=0; i<size-1; i++){
            if(nums[res] != nums[i+1]){
                res++;
                nums[res] = nums[i+1];
            }
        }
        return res + 1;
    }
};

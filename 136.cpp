/*********************************************
*     ------------------------
*     ------------------------
*     file name: 136.cpp
*     author   : @ JY
*     date     : 2019--10--06
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int singleNumber(vector<int>& nums){
            int size = nums.size();
            int n = 0;
            for(int i=0; i<size-1; i++){
                n = n ^ nums[i];
            }
            return n;
        }
};

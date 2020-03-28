/*********************************************
*     ------------------------
*     ------------------------
*     file name: 260.cpp
*     author   : @ JY
*     date     : 2020--03--06
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        vector<int> singleNumber(vector<int>& nums){
            int __size = nums.size();
            int __resa = 0;
            for(int num : nums){
                __resa = __resa ^ num;
            }
            int __flag = __resa&(~__resa+1);
            int __resb = __resa;
            for(int num : nums){
                if(num & __flag){
                    __resb = __resb ^ num;
                }
            }
            vector<int> __res;
            __res.push_back(__resb);
            __res.push_back(__resa^__resb);
            return __res;
        }
};

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 137.cpp
*     author   : @ JY
*     date     : 2019--10--08
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int singleNumber(vector<int>& nums){
            int res = 0;
            for(int i=0; i<32; i++){
                int tmp = 0;
                for(int num : nums){
                    if(num & 1<<i){
                        tmp++;
                    }
                }
                if(tmp%3){
                    res = res | (1<<i);
                }
            }
            return res;
        }
};

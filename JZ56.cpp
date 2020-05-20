/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ56.cpp
*     author   : @ JY
*     date     : 2020--05--19
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int xorN = 0;
        for(int i=0; i<nums.size(); ++i){
            xorN = xorN ^ nums[i];
        }
        int a = xorN&(~xorN+1);
        int b = xorN;
        for(int i=0; i<nums.size(); ++i){
            if(nums[i]&a){
                b = b ^ nums[i];
            }
        }
        a = xorN ^ b;
        return vector<int>{a,b};
    }
    int singleNumber(vector<int>& nums) {
        int res   = 0;
        int count = 0;
        for(int i=0; i<=31; ++i){
            count = 0;
            for(int n : nums){
                if(n&(1<<i)){
                    ++count;
                }
            }
            if(count%3){
                res = res ^(1<<i);
            }
        }
        return res;
    }
};

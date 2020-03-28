/*********************************************
*     ------------------------
*     ------------------------
*     file name: 368.cpp
*     author   : @ JY
*     date     : 2020--02--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        vector<int> __res;
        int __size = nums.size();
        if(!__size){
            return __res;
        }
        sort(nums.begin(),nums.end());
        vector<int> __dp(__size,1);
        vector<int> __pt(__size,-1);
        int ml = 0;
        int mi = -1;
        for(int i=0; i<__size; ++i){
            for(int j=0; j<i; ++j){
                if(!(nums[i]%nums[j]) && (__dp[i]<__dp[j]+1)){
                    __dp[i] = __dp[j] +1;
                    __pt[i] = j;
                }
            }
            if(ml < __dp[i]){
                ml = __dp[i];
                mi = i;
            }
        }
        while(mi != -1){
            __res.push_back(nums[mi]);
            mi = __pt[mi];
        }
        reverse(__res.begin(),__res.end());
        return __res;
    }
};

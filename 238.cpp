/*********************************************
*     ------------------------
*     ------------------------
*     file name: 238.cpp
*     author   : @ JY
*     date     : 2020--02--26
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //int __size = nums.size();
        //vector<int> __res(__size,0);
        //int __l[__size];
        //int __r[__size];
        //__l[0]         = 1;
        //__r[__size-1]  = 1;
        //for(int i=1; i<__size; ++i){
            //__l[i] = __l[i-1] * nums[i-1];
        //}
        //for(int i=__size-2; i>=0; --i){
            //__r[i] = __r[i+1]*nums[i+1];
        //}
        //for(int i=0; i<__size; ++i){
            //__res[i] = __l[i] * __r[i];
        //}

        int __size = nums.size();
        vector<int> __res(__size,0);
        int __l[__size];
        __l[0]     = 1;
        for(int i=1; i<__size; ++i){
            __l[i] = __l[i-1] * nums[i-1];
        }
        int __tmp  = 1;
        for(int i=__size-1; i>=0; --i){
            __l[i] = __tmp * __l[i];
            __tmp  = __tmp * nums[i];
        }
        return __l;
    }

};

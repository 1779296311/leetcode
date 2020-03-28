/*********************************************
*     ------------------------
*     ------------------------
*     file name: 852.cpp
*     author   : @ JY
*     date     : 2020--02--23
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& A) {
        int __size = A.size();
        int __res  = 0;
        int __max  = A[0];
        for(int i=1; i<__size; ++i){
            if(__max < A[i]){
                __max   = A[i];
                __res = i;
            }
        }
        return __res;
    }
};

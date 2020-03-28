/*********************************************
*     ------------------------
*     ------------------------
*     file name: 191.cpp
*     author   : @ JY
*     date     : 2020--02--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int __res = 0;
        while(n){
            n = n &(n-1);
            ++__res;
        }
        return __res;
    }
};

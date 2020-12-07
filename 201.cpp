/*********************************************
*     ------------------------
*     ------------------------
*     file name: 201.cpp
*     author   : @ JY
*     date     : 2020--11--07
**********************************************/
#include <iostream>
#include <stdlib.h>

class Solution{
    public:
        int rangeBitwiseAnd(int m, int n){
            int shift = 0;
            while(m < n){
                m >>= 1, n >>= 1;;
                ++shift;
            }
            return m << shift;
        }
        int rangeBitwiseAnd_be(int m, int n){
            while(m < n)n &= n - 1;
            return n;
        }
};

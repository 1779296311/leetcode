/*********************************************
*     ------------------------
*     ------------------------
*     file name: 342.cpp
*     author   : @ JY
*     date     : 2020--02--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool isPowerOfFour(int n){
        if(n <=0 || n&(n-1)){
            return false;
        }
        if(n == 1){
            return true;
        }
        int k = 0;
        while(!((n>>=1)&1)){
            ++k;
        }
        return k&1;
    }
};

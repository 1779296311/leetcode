/*********************************************
*     ------------------------
*     ------------------------
*     file name: 338.cpp
*     author   : @ JY    
*     data     : 2019--09--13
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        vector<int> countBits(int num){
            vector<int> memo(num+1, 0);
            memo[0]  = 0;
            for(int i=1; i<=num; i++){
                memo[i]  = memo[i >> 1] + i&1;
            }
            return memo;
        }
};

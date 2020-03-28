/********************************************* 
*     ------------------------                 
*     ------------------------                 
*     file name: climbStairs.cpp
*     author   : @JY    
*     data     : 2019--09--09
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int limbStairs(int n){
            vector<int> memo(n+1, -1);
            memo[0]   = 1;
            memo[1]   = 1;

            for(int i=2; i<n; i++){
                memo[i] = memo[i-1] + memo[i - 2];
            } 
            return memo[n];
        }
}; 

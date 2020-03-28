/*********************************************
*     ------------------------
*     ------------------------
*     file name: 279.cpp
*     author   : @ JY
*     data     : 2019--09--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int numSquares(int n){
            vector<int> memo(n+1, INT_MAX);
            memo[0] = 0;
            for(int i=1; i<=n; i++){
                for(int j=1; j*j<=i; j++){
                    if(memo[i-j*j]+1 < memo[i]){
                        memo[i]  = memo[i-j*j] + 1;
                    }
                }
            }
            return memo[n];
        }
        int numSquares(int n){
            vector<int> dp(n+1);
            dp[0] = 0;
            for(int i=1; i<=n; ++i){
                for(int j=1; j*j<=i; ++j){
                    dp[i] = min(dp[i],dp[i-j*j]+1);
                }
            }
            return dp[n];
        }
};

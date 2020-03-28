/*********************************************
*     ------------------------
*     ------------------------
*     file name: L_437.cpp
*     author   : @ JY
*     data     : 2019--09--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vectro>
using  namespace  std;

class Solution{
    public:
        int copyBooks(vector<int> pages, int k){
            int size = pages.size();
            if(size == 0){
                return 0;
            }
            if(size == 1){
                return pages[0];
            }
            if(k>size){
                k = size;
            }
            vector<vector<int>> memo(k+1, vector<int>(size+1, INT_MAX));
            memo[0][0] = 0;
            for(int i=1; i<k; i++){
                memo[i][0]  = 0;
                for(int j=1; j<size; j++){
                    int sum = 0;
                    for(int l=j; l>=0; l--){
                        memo[i][j] = min(memo[i][j],max(memo[i-1][l] , sum));
                        if(l>0){
                            sum = sum + pages[l];
                        }
                    }
                }
            }
            return memo[k][size];
        }

        int copyBooks(vector<int> pages, int k){
            int size = pages.size();
            if(!size){
                return 0;
            }
            if(k>size){
                k = size;
            }
            vector<vector<int>> dp(k+1,vector<int>(size+1,INT_MAX));
            dp[0][0] = 0;
            for(int i=1; i<=k; ++k){
                dp[i][0] = 0;
                for(int j=0; j<=size; ++j){
                    int num = 0;
                    for(int l=j; l>=0; --l){
                        dp[i][j] = min(dp[i][j],max(num,dp[i-1][l]));
                        if(l>0){
                            sum = sum + pages[l-1];
                        }
                    }
                }
            }
            return memo[k][size];
        }
};

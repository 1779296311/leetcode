/*********************************************
*     ------------------------
*     ------------------------
*     file name: 123.cpp
*     author   : @ JY    
*     data     : 2019--09--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int maxProfit(vector<int>& prices){
            int size = prices.size();
            if(size == 1 || size == 0){
                return 0;
            }
            int k = 2;
            int l = (1<<k)+1;
            vector<vector<int>> memo(size+1, vector<int>(l+1, INT_MIN));
            memo[0][1] = 0;
            for(int i=1; i<=size; i++){
                for(int j=1; j<=l; j+=2){
                    memo[i][j] = memo[i-1][j];
                    if(j>1 && i>1 && memo[i-1][j-1] != INT_MIN){
                        memo[i][j] = max(memo[i][j], memo[i-1][j-1] + prices[i-1] -prices[i-2]);
                    }
                }
                for(int j=2; j<=l; j+=2){
                    memo[i][j] = memo[i-1][j-1];
                    if(j>2 && i>1 && memo[i-1][j-2] != INT_MIN ){
                        memo[i][j] = max(memo[i-1][j-2] + prices[i-1] - prices[i-2],memo[i][j]);
                    }
                    if(i>1 && memo[i-1][j] != INT_MIN){
                        memo[i][j] = max(memo[i-1][j] + prices[i-1] - prices[i-2], memo[i][j]);
                    }
                }
            }
            int maxS = 0;
            for(int i=1; i<=l; i+=2){
                maxS = max(maxS,memo[size][i]);
            }
            return maxS;
        }
};

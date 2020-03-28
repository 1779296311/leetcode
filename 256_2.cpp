/*********************************************
*     ------------------------
*     file name: 256_2.cpp
*     author   : @ JY
*     data     : 2019--09--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <climits>
using  namespace  std;

class Solution{
    public:
        int minCostII(vector<vector<int>>& costs){
            int len     = costs.size();
            int l       = costs[0].size();
            int minS    = 0;
            int min_1;
            int min_2;
            int index_1 = 0;
            int index_2 = 0;
            vector<vector<int>> memo(len + 1, vector<int>(l));

            for(int i=1; i<=len; i++){
                min_1 = min_2 = INT_MAX;
                for(int j=0; i<l; j++){
                    if(costs[i-1][j] < min_1){
                        min_2   = min_1;
                        index_2 = index_1;
                        min_1   = costs[i-1][j];
                        index_1 = j;
                    }else if(costs[i-1][j] < min_2){
                        min_2   = costs[i-1][j];
                        index_2 = j;
                    }
                }
                for(int j=0; j<l; j++){
                    if(j != index_1){
                        memo[i][j] = min_1 + costs[i][j];
                    }else{
                        memo[i][j] = min_2 + costs[i][j];
                    }
                }
            }
            for(int i=0; i<l; i++){
                if(minS < memo[len][i]){
                    minS = memo[len][i];
                }
            }
            return minS;
        }
};

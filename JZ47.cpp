/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ47.cpp
*     author   : @ JY
*     date     : 2020--05--18
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size(),vector<int>(grid[0].size(),0));
        dp[0][0] = grid[0][0];
        for(int i=1; i<grid[0].size(); ++i){
            dp[0][i] = grid[0][i] + dp[0][i-1];
        }
        for(int i=1; i<grid.size(); ++i){
            dp[i][0] = grid[i][0] + dp[i-1][0];
        }
        for(int i=1; i<grid.size(); ++i){
            for(int j=1; j<grid[0].size(); ++j){
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])+grid[i][j];
            }
        }
        return dp[dp.size()-1][dp[0].size()-1];
    }
    int maxValue1(vector<vector<int>>& grid){
        int sizeI = grid.size();
        int sizeJ = grid[0].size();
        vector<int> dp(sizeJ,0);
        dp[0] = grid[0][0];
        for(int i=1; i<sizeJ; ++i){
            dp[i] = dp[i-1] + grid[0][i];
        }
        for(int i=1; i<sizeI; ++i){
            for(int j=0; j<sizeJ; ++j){
                if(!j){
                    dp[j] = dp[j] + grid[i][j];
                }else{
                    dp[j] = max(dp[j],dp[j-1]) + grid[i][j];
                }
            }
        }
        return dp[sizeJ-1];
    }
};


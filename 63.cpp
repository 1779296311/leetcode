/*********************************************
*     ------------------------
*     ------------------------
*     file name: 63.cpp
*     author   : @ JY
*     data     : 2019--09--13
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int uniquePathWithObstacles(vector<<vector<int>>& obstacleGrid){
            if(obstacleGrid[0][0] == 1){
                return 0;
            }
            int hig = obstacleGrid.size();
            int wid = obstacleGrid[0].size();
            vector<vector<int>> memo(hig, vector<int>(wid,0));
            memo[0][0]   = 1;
            for(int i=0; i<hig; i++){
                for(int j=0; j<wid; j++){
                    if(obstacleGrid[i][j] == 1){
                        memo[i][j]  = 0;
                    }else{
                        if(i>0){
                            memo[i][j] = memo[i][j] + memo[i-1][j];
                        }
                        if(j>0){
                            memo[i][j] = memo[i][j] + memo[i][j-1];
                        }
                    }
                }
            }
            return memo[hig-1][wid-1];
        }
        int uniquePath_2(vector<<vector<int>>& obs){
            if(obs[0][0]){
                return 0;
            }
            int sizeH = obs.size();
            int sizeL = obs[0].size();
            vector<int> dp(sizeL,0);
            dp[0]     = 1;
            for(int i=0; i<sizeH; ++i){
                for(int j=0; j<sizeL; ++j){
                    if(obs[i][j]){
                        dp[j] = 0;
                    }else if(j>0){
                        dp[j] = dp[j] + dp[j-1];
                    }
                }
            }
            return dp[sizeL-1];
        }
};

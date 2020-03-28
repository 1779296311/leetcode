/*********************************************
*     ------------------------
*     ------------------------
*     file name: 256.cpp
*     author   : @ JY    
*     data     : 2019--09--13
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <climits>
using  namespace  std;

class Solution{
    public:
        int drawHouse(vector<vector<int>>& costs){
            int len         = costs.size();
            int color_num   = 3;
            vector<vector<int>> memo(len, vector<int>(color_num,INT_MAX));

            for( int i=0; i<color_num; i++){
                memo[0][i] = costs[0][i];
            }
            for(int i=1; i<len; i++){
                for(int j=0; j<color_num; j++){
                    for(int k=0; k<color_num; k++){
                        if(k != j && memo[i-1][k] + costs[i][j] < memo[i][j]){
                            memo[i][j]   = memo[i-1][k] + costs[i][j];
                        }
                    }
                }
            }

            return min(min(memo[len-1][0],memo[len-1][1]),memo[len-1][2]);
        }
        int drawHouse(int color_num, vector<vector<int>>& costs){
            int size = costs.size();
            vector<vector<int>> dp(size,vector<int>(color_num,INT_MAX));
            for(int i=0; i<size; ++i){
                for(int j=0; j<color_num; ++j){
                    if(!i){
                        dp[i][j] = costs[i][j];
                        continue;
                    }
                    for(int k=0; k<color_num; ++k){
                        if(j != k){
                            dp[i][j] = min(dp[i][j],dp[i-1][k]);
                        }
                    }
                    dp[i][j] = dp[i][j] + costs[i][j];
                }
            }
            int __res = INT_MAX;
            for(int i=0; i<color_num; ++i){
                __res = min(__res,dp[size-1][i]);
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;

    int len = 3;
    int num[][3]  = {{14,2,11},{11,14,5},{14,3,10}};
    vector<vector<int>> costs(len, vector<int>(3));
    for(int i=0; i<len; i++){
        for(int j=0; j<3; j++){
            costs[i][j] = num[i][j];
        }
    }
    cout <<te.drawHouse(costs)<<endl;
    return 0;
}
    //for(int i=0; i<len; i++){
    //    for(int j=0; j<3; j++){
    //        cout <<memo[i][j]<<"-- " ;
    //    }
    //}

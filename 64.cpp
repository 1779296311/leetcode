/********************************************* 
*     ------------------------
*     file name: 64.cpp
*     author   : @ JY
*     data     : 2019--09--11
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int minPathSum(vector<vector<int>>& grid){
            int len  = grid.size();
            int list = grid[0].size();

            vector<vector<int>> memo(len,vector<int>(list));

            memo[0][0] = grid[0][0];
            for(int i=1; i<list; i++){
                memo[0][i] = memo[0][i-1] + grid[0][i];
            }
            for(int i=1; i<len; i++){
                memo[i][0] = memo[i-1][0] + grid[i][0];
            }

            for(int i=1; i<len; i++){
                for(int j=1; j<list; j++){
                    memo[i][j] = min(memo[i-1][j], memo[i][j-1]) + grid[i][j];
                }
            }
            for(int i=0; i<len; i++){
                for(int j=0; j<list; j++){
                    cout <<memo[i][j]<<"-- ";
                }
                cout <<endl;
            }
            return memo[len-1][list-1];
        }
        int minPathSum(vector<vector<int>>& grid){
            int sizeH = grid.size();
            int sizeL = grid[0].size();
            int now   = 0;
            vector<vector<int>> dp(2,vector<int>(sizeL,0));
            for(int i=0; i<sizeH; ++i){
                for(int j=0; j<sizeL; ++j){
                    dp[now][j] = grid[i][j];
                    if(!i && !j){
                        continue;
                    }
                    int a,b;
                    a = (i>0)?dp[1-now][j]:INT_MAX;
                    b = (j>0)?dp[now][j-1]:INT_MAX;
                    dp[now][j] += min(a,b);
                }
                now = 1 - now;
            }
            return dp[now][sizeL-1];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int len  = 2;
    int list = 3;
    int tes[len][list]= {{1,2,5},{3,2,1}};
    vector<vector<int>> nums(len, vector<int>(list));
    for(int i=0; i<len; i++){
        for(int j=0; j<list; j++){
            nums[i][j] = tes[i][j];
        }
    }for(int i=0; i<len; i++){
                for(int j=0; j<list; j++){
                    cout <<nums[i][j]<<"-- ";
                }
                cout <<endl;
            }

    cout <<te.minPathSum(nums)<<endl;

    return 0;
}

    //for(int i=0; i<len; i++){
    //    for(int j=0; j<list; j++){
    //        cout <<tes[i][j];
    //    }
    //    cout <<endl;

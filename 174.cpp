/*********************************************
*     ------------------------
*     ------------------------
*     file name: 174.cpp
*     author   : @JY
*     data     : 2019--09--11
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int calulateMinimumHp(vector<int>& dungeon){
            int len = dungeon.size();
            int list= dungeon[0].size();
            if(len == 0){
                return 0;
            }

            vactor<vector<int>> memo(len, vector<int>(list));
            memo[len-1][list-1] = max(1, 1-dungeon[len-1][list-1]);

            for(int i=len-2; i>=0; i--){
                memo[i][list-1] = max(1,memo[i+1][list-1] - dungeon[i][list-1]);
            }
            for(int i=list-2; i>=0; i--){
                memo[len-1][i] = max(1,memo[len-1][i+1] - dungeon[len-1][i]);
            }

            for(int i=len-2; i>=0; i-- ){
                for(int j=list-2; j>=0; j--){
                    int memo_min = min(memo[i][j+1], memo[i+1][j]);
                    memo[i][j]   = max(1, memo_min - dungeon[i][j]);
                }
            }
            return memo[0][0];
        }
};

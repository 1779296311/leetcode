/*********************************************
*     ------------------------
*     ------------------------
*     file name: 62.cpp
*     author   : @ JY
*     date     : 2019--09--23
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
问总共有多少条不同的路径？*/
class Solution{
    public:
        int uniquePaths(int m, int n){
            vector<vector<int>> memo(n, vector<int>(m,0));
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    if(!j || !i){
                        memo[i][j] = 1;
                    }else{
                        memo[i][j] = memo[i-1][j] + memo[i][j-1];
                    }
                }
            }
            return memo[m-1][n-1];
        }
};

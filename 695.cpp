/*********************************************
*     ------------------------
*     ------------------------
*     file name: 695.cpp
*     author   : @ JY
*     date     : 2020--02--21
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int maxAreafIsLand(vector<vector<int>>& grid) {
        int __res  = 0;
        int __size = grid.size();
        for(int i=0; i<__size; ++i){
            for(int j=0; j<grid[0].size(); ++j){
                if(grid[i][j] == 1){
                    int num = 0;
                    dfs(grid,i,j,num);
                    if(num > __res){
                        __res = num;
                    }
                }
            }
        }
        return __res;
    }
    void dfs(vector<vector<int>>& grid, int x, int y, int &num){
        if(x < 0 || y < 0 || x>=grid.size() || y>=grid[0].size() || grid[x][y] != 1){
            return;
        }
        ++num;
        grid[x][y] = 0;
        dfs(grid,x+1,y,num);
        dfs(grid,x-1,y,num);
        dfs(grid,x,y+1,num);
        dfs(grid,x,y-1,num);
    }
};

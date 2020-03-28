/*********************************************
*     ------------------------
*     ------------------------
*     file name: 200.cpp
*     author   : @ JY
*     date     : 2020--02--21
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int __res  = 0;
        int __size = grid.size();
        for(int i=0; i<__size; ++i){
            for(int j=0; j<grid[0].size(); ++j){
                if(grid[i][j] == '1'){
                    ++__res;
                    dfs(grid,i,j);
                }
            }
        }
        return __res;
    }
    void dfs(vector<vector<char>>& grid, int x, int y){
        if(x < 0 || y < 0 || x>=grid.size() || y>=grid[0].size() || grid[x][y] != '1'){
            return;
        }
        grid[x][y] = '0';
        dfs(grid,x+1,y);
        dfs(grid,x-1,y);
        dfs(grid,x,y+1);
        dfs(grid,x,y-1);
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    return 0;
}

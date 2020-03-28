/*********************************************
*     ------------------------
*     ------------------------
*     file name: 463.cpp
*     author   : @ JY
*     date     : 2020--02--21
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int __sizex = grid.size();
        int __sizey = grid[0].size();
        int __res   = 0;
        for(int i=0; i<__sizex; ++i){
            for(int j=0; j<__sizey; ++j){
                if(grid[i][j]){
                    if(i<=0 || !grid[i-1][j]){
                        ++__res;
                    }
                    if(i>=__sizex-1 || !grid[i+1][j]){
                        ++__res;
                    }
                    if(j<=0 || !grid[i][j-1]){
                       ++__res;
                    }
                    if(j>=__sizey-1 || !grid[i][j+1]){
                        ++__res;
                    }
                }
            }
        }
        return __res;
    }
};

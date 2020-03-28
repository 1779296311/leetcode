/*********************************************
*     ------------------------
*     ------------------------
*     file name: 361.cpp
*     author   : @ JY    
*     data     : 2019--09--13
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int maxKilledEnemies(vector<vector<char>>& grid){
            int len = grid.size();
            int list= grid[0].size();
            vector<vector<int>> tmp(len, vector<int>(list, 0));
            vector<vector<int>> memo(len, vector<int>(list, 0));

            //Up
            for(int i=0; i<len; i++){
                for(int j=0; j<list; j++){
                    if(grid[i][j] == 'w'){
                        memo[i][j] = 0;
                    }else if(grid[i][j] == 'e'){
                        memo[i][j] = ((i>0)?memo[i-1][j]:0)+1;
                    }else if(grid[i][j] == '0'){
                        memo[i][j] = ((i>0)?memo[i-1][j]:0);
                    }
                    tmp[i][j]   = tmp[i][j] + memo[i][j];
                }
            }
            //Right
            for(int i=0; i<len; i++){
                for(int j=0; j<list; j++){
                    if(grid[i][j] == 'w'){
                        memo[i][j]  = 0;
                    }else if(grid[i][j] == 'e'){
                        if(j>0){
                            memo[i][j]  = memo[i][j-1] + 1;
                        }else{
                            memo[i][j]  = 1;
                        }
                    }else if(grid[i][j] == '0'){
                        if(j>0){
                            memo[i][j]  = memo[i][j-1];
                        }else{
                            memo[i][j]  = 0;
                        }
                    }
                    tmp[i][j]   = tmp[i][j] + memo[i][j];
                }
            }
            //Down
            for(int i=len-1; i>=0; i--){
                for(int j=0; j<list; j++){
                    if(grid[i][j] == 'w'){
                        memo[i][j]  = 0;
                    }else if(grid[i][j] == 'e'){
                        if(i< len-1){
                            memo[i][j]  = memo[i+1][j] + 1;
                        }else{
                            memo[i][j]  = 1;
                        }
                    }else if(grid[i][j] == '0'){
                        if(i < len-1){
                            memo[i][j]  = memo[i+1][j];
                        }else{
                            memo[i][j]  = 0;
                        }
                    }
                    tmp[i][j]   = tmp[i][j] + memo[i][j];
                }
            }
            //Left
            for(int i=0; i<len; i++){
                for(int j=list-1; j>=0; j--){
                    if(grid[i][j] == 'w'){
                        memo[i][j]  = 0;
                    }else if(grid[i][j] == 'e'){
                        if(j<list-1){
                            memo[i][j]  = memo[i][j-1] + 1;
                        }else{
                            memo[i][j]  = 1;
                        }
                    }else if(grid[i][j] == '0'){
                        if(j<list-1){
                            memo[i][j]  = memo[i][j-1];
                        }else{
                            memo[i][j]  = 0;
                        }
                    }
                    tmp[i][j]   = tmp[i][j] + memo[i][j];
                }
            }

            int max = 0;
            for(int i=0; i<len; i++){
                for( int j=0; j<list; j++){
                    if(tmp[i][j] > max && grid[i][j] == '0'){
                        max = tmp[i][j];
                    }
                }
            }

            return max;
        }
};

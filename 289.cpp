/*********************************************
*     ------------------------
*     ------------------------
*     file name: 289.cpp
*     author   : @ JY
*     date     : 2019--10--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        void gameOfLife(vector<vector<int>>& board){
            if(!board.size()){
                return;
            }
            int H = board.size();
            int L = board[0].size();
            int direction[8][2] = {
                {-1,0},{-1,1},
                {0,1}, {1,1},
                {1,0},{1,-1},
                {0,-1},{-1,-1}
            };
            for(int i=0; i<H; i++){
                for(int j=0; j<L; j++){
                    for(int k=0; k<8; k++){
                        int tmp_i = i + direction[k][0];
                        int tmp_j = j + direction[k][1];
                        if(tmp_i>=0 && tmp_i<H && tmp_j>=0 && tmp_j<L){
                            board[i][j] = board[i][j] + ((board[tmp_i][tmp_j] & 1)<<1);
                        }
                    }
                }
            }
            for(int i=0; i<H; i++){
                for(int j=0; j<L; j++){
                    int tmp = board[i][j] >> 1;
                    if(tmp == 3){
                        board[i][j] = 1;
                    }else if(tmp == 2){
                        board[i][j] = board[i][j] & 1;
                    }else{
                        board[i][j] = 0;
                    }
                }
            }
        }
};

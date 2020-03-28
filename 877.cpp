/*********************************************
*     ------------------------
*     file name: 877.cpp
*     author   : @ JY
*     date     : 2019--09--18
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        bool stoneGame(vector<int>& piles){
            int size = piles.size();
            if(size == 1 || size == 2){
                return true;
            }
            if(size == 0){
                return false;
            }
            vector<vector<int>> memo(size, vector<int>(size,0));
            for(int i=0; i<size; i++){
                memo[i][i] = piles[i];
            }
            for(int distance=1; distance<size; distance++){
                for(int begin=0; begin<size-distance; begin++){
                    int end = begin + distance;
                    memo[begin][end] = max(piles[begin] - memo[begin+1][end], piles[end] - memo[begin][end-1]);
                }
            }
            return memo[0][size-1]>0;
        }
};


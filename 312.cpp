/*********************************************
*     file name: 312.cpp
*     author   : @ JY
*     date     : 2019--09--18
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
/*
有n个气球，编号为0到n-1，每个气球上都标有一个数字，这些数字存在数组nums中现在要求你戳破所有的气球每当你戳破一个气球i时你可以获得nums[left]*nums[i]*nums[right]个硬币这里的left和right代表和i相邻的两个气球的序号注意当你戳破了气球i后，气球left和气球right就变成了相邻的气球。
求所能获得硬币的最大数量。
**/
class Solution{
    public:
        int maxCoin(::std::vector<int>& coins){
            int size = coins.size();
            if(size == 0){
                return 0;
            }
            vector<int> Coin(size+2,0);
            Coin[0]  =  Coin[size+1] = 1;
            for(int i=1; i<=size; i++){
                Coin[i] = coins[i-1];
            }

            vector<vector<int>> memo(size+2, vector<int>(size+2, 0));
            for(int i=0; i<=size; i++){
                memo[i][i+1] = 0;
            }
            // memo[begin][end]  ~~ (begin+1 -- end-1)
            for(int distance=2; distance<size+2; distance++){
                for(int begin=0; begin<size+2-distance; begin++){
                    int end = begin + distance;
                    for(int bomb=1; bomb<distance; bomb++){
                        memo[begin][end] = max(memo[begin][end], Coin[begin]*Coin[begin+bomb]*Coin[end] + memo[begin][begin+bomb] + memo[begin+bomb][end]);
                    }
                }
            }
            return memo[0][size+1];
        }
};

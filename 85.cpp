/*********************************************
*     ------------------------
*     ------------------------
*     file name: 85.cpp
*     author   : @ JY
*     date     : 2019--09--24
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。*/
class Solutio{
     public:
         int maximalRectangle(vector<vector<int>>& matrix){
             if(!matrix.size()){
                 return 0;
             }
             int num   = matrix.size();
             int size  = matrix[0].size();
             int __max = 0;

             vector<int> memo(size, 0);
             for(int i=0; i<num; i++){
                 for(int j=0; j<size; j++){
                     if(matrix[i][j] == 1){
                         memo[j] = memo[j] + 1;
                     }else{
                         memo[j] = 0;
                     }
                 }
                 __max = max(__max, Stack(memo));
             }
             return __max;
         }
    private:
         int Stack(vector<int>& memo){
             memo.push_back(0); // very importment!!!!!!!!!!!!!!
             int len = memo.size();
             int MAX = 0;
             stack<int> sta;
             for(int i=0; i<len; i++){
                 while(!sta.empty() && memo[i] <= memo[sta.top()]){
                     int old_top = sta.top();
                     sta.pop();
                     MAX = max(MAX, memo[old_top]*(sta.empty()?i:i-sta.top()-1));
                 }
                 sta.push(i);
             }
             memo.pop_back();
             return MAX;
         }
};

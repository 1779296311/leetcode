/*********************************************
*     ------------------------
*     ------------------------
*     file name: 240.cpp
*     author   : @ JY
*     date     : 2020--06--27
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
//编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：
//每行的元素从左到右升序排列。
//每列的元素从上到下升序排列。
class Solution{
    public:
        bool searchMatrix(::std::vector<::std::vector<int>>& matrix, int k){
            int size1 = matrix.size();
            if(size1==0)return false;
            int size2 = matrix[0].size();
            int i     = 0;
            int j     = size2-1;
            while(i<size1 && j>=0){
                if(matrix[i][j] == k){
                    return true;
                }else if(matrix[i][j] > k){
                    --j;
                }else{
                    ++i;
                }
            }
            return false;
        }
};

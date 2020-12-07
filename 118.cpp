/*********************************************
*     ------------------------
*     ------------------------
*     file name: 118.cpp
*     author   : @ JY
*     date     : 2020--10--01
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>

class Solution{
    public:
        std::vector<std::vector<int>> generate(int numRows){
            std::vector<std::vector<int>> res;
            for(int i=0; i<numRows; ++i)res.push_back(std::vector<int>(i+1, 1));
            for(int i=0; i<numRows; ++i){
                for(int j=1; j<i; ++j){
                    res[i][j] = res[i-1][j-1] + res[i-1][j];
                }
            }
            return res;
        }
};

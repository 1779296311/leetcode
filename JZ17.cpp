/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ17.cpp
*     author   : @ JY
*     date     : 2020--05--23
**********************************************/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdlib.h>
class Solution {
public:
    ::std::vector<int> printNumbers(int n) {
        ::std::vector<int>res;
        int size = (int)::std::pow(10.0,n);
        for(int i=1; i<size; ++i){
            res.push_back(i);
        }
        return res;
    }
};

/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ66.cpp
*     author   : @ JY
*     date     : 2020--05--22
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
class Solution {
public:
    ::std::vector<int> constructArr(::std::vector<int>& a) {
        int left  = 1;
        int right = 1;
        ::std::vector<int> res(a.size(),0);
        for(int i=0; i<a.size(); ++i){
            res[i] = left;
            left   = left * a[i];
        }
        for(int i=a.size()-1; i>=0; --i){
            res[i] = res[i]*right;
            right  = right*a[i];
        }
        return res;
    }
};

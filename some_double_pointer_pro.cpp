/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_double_pointer_pro.cpp
*     author   : @ JY
*     date     : 2020--07--24
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
class Solution{
   public:
//413. 等差数列划分
        int numberOfArithmetic(std::vector<int>& A){
            int size = A.size();
            if(size<=2)return 0;
            int l = 0;
            int r = 1;
            int d = A[r++] - A[l];
            int res =  0;
            int n = 0;
            while(r<size){
                if(A[r]-A[r-1] != d){
                    if((n=r-l-1)>=1)res += (n*(n+1))>>1;
                    l = r - 1;
                    d = A[r] - A[r-1];
                }
                ++r;
            }
            if((n=r-l-1)>=1)res += (n*(n+1))>>1;
            return res;
        }
};

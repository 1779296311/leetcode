/*********************************************
*     ------------------------
*     ------------------------
*     file name: 171.cpp
*     author   : @ JY
*     date     : 2020--04--08
**********************************************/
#include <iostream>
#include <cmath>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
            int string_To_Int(string num){
            if(!num.length()){
                return 0;
            }
            int __res = 0;
            int len   = num.length();
            for(char i : num){
                __res = __res + (i-'A'+1)*addN(26,--len);
            }
            return __res;
        }
        int addN(int i,int n){
            return (int)pow(i,n);
        }

};

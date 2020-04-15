/*********************************************
*     ------------------------
*     ------------------------
*     file name: 168.cpp
*     author   : @ JY
*     date     : 2020--04--08
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        string int_To_String(int num){
            if(num<1){
                return "";
            }
            int size     = 26;
            string __res = "";
            int len      = 0;
            int cur      = 1;
            while(num >= cur){
                num = num - cur;
                cur = cur * size;
                ++len;
            }
            while(len--){
                cur   = cur/size;
                __res = __res + string(1,'A'+num/cur);
                num   = num % cur;
            }
            return __res;
        }
};

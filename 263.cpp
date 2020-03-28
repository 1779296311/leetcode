/*********************************************
*     ------------------------
*     ------------------------
*     file name: 263.cpp
*     author   : @ JY
*     date     : 2019--10--19
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        bool isUgly(int num){
            while(num % 2 == 0){
                num = num >> 1;
            }
            while(num % 3 == 0){
                num = num / 3;
            }
            while(num % 5 == 0){
                num = num / 5;
            }
            return num == 1;
        }
};

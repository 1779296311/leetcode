/*********************************************
*     ------------------------
*     ------------------------
*     file name: 202.cpp
*     author   : @ JY
*     date     : 2019--10--17
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        bool isHappy(int n){
            string str;
            for(int i=0; i<6; i++){
                str = to_string(n);
                int tmp = 0;
                for(char x : str){
                    tmp = tmp + (x-'0') * (x-'0');
                }
                if(tmp == 1){
                    return true;
                }else if(tmp == 4){
                    return false;
                }
                n = tmp;
            }
            return false;
        }
};

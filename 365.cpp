/*********************************************
*     ------------------------
*     ------------------------
*     file name: 365.cpp
*     author   : @ JY
*     date     : 2020--02--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        int __t;
        if(x==z||y==z||(x+y)==z){
            return true;
        }
        if(x+y<z){
            return false;
        }
        while(x){
            __t = y % x;
            y   = x;
            x   = __t;
        }
        return (!z) || (y && z>0 && !(z%y));
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    te.canMeasureWater(12,27,0);
    return 0;
}

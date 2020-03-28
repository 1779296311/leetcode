/*********************************************
*     ------------------------
*     ------------------------
*     file name: 384.cpp
*     author   : @ JY
*     date     : 2020--02--23
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    double myPow(double x, int n){
        if(!n){
            return 1;
        }
        int __n   = n;
        while(!(__n&1)){
            x    *= x;
            __n  /= 2;
        }
        __n /= 2;
        if(!__n){
            return n>0?x:1/x;
        }
        double __res = x;
        x            = x * x;
        __n          = __n>0?__n:-__n;
        while(true){
            if(__n&1){
                __res = __res * x;
                if(1 == __n){
                    return n>0?__res:1/__res;
                }
            }
            x    *= x;
            __n  /= 2;
        }
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    for(int i=0; i<10; i++){
        cout<<te.myPow(4.0, i)<<endl;
        cout<<te.myPow(4.0, i*-1)<<endl;
    }
    return 0;
}

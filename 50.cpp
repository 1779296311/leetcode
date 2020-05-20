/*********************************************
*     ------------------------
*     ------------------------
*     file name: 50.cpp
*     author   : @ JY
*     date     : 2020--05--09
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    double myPow(double x, int n) {
        double tmp = x;
        double res = 1;
        int flag   = n>0?1:0;
        while(n){
            if(n&1){
                res = res*tmp;
            }
            tmp = tmp*tmp;
            n   = n/2;
        }
        return flag?res:1/res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.myPow(9,3)<<endl;
    return 0;
}

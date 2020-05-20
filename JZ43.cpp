/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ43.cpp
*     author   : @ JY
*     date     : 2020--05--13
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int countDigitOne(int n) {
        long long digit = 1;
        long long low   = 0;
        long long high  = n/10;
        long long res   = 0;
        long long cur   = n%10;
        while(cur || high){
            if(cur == 0){
                res = res + high*digit;
            }else if(cur == 1){
                res = res + high*digit + low + 1;
            }else{
                res = res + (high+1)*digit;
            }
            low   = low + cur*digit;
            cur   = high%10;
            high  = high/10;
            digit = digit*10;
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.countDigitOne(13)<<endl;
    return 0;
}

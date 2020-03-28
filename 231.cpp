/*********************************************
*     ------------------------
*     ------------------------
*     file name: 231.cpp
*     author   : @ JY
*     date     : 2020--02--22
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return (1073741824==n) ||(n>0 && n<1073741824 && n==((2*n-1)&~(n-1)));
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.isPowerOfTwo(1073741824)<<endl;
    return 0;
}

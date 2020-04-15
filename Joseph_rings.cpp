/*********************************************
*     ------------------------
*     ------------------------
*     file name: Joseph_rings.cpp
*     author   : @ JY
*     date     : 2020--04--07
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int Joseph_rings(int m, int n){
            int __res = 0;
            for(int i=2; i<=n; ++i){
                __res = (__res+m)%i;
            }
            return __res+1;
        }
        int Joseph_rings_1(int m, int n){
            if(n <= 1){
                return 0;
            }
            return (Joseph_rings_1(m,n-1)+m)%n;
        }
        int Joseph_rings_2(int m, int n){
            return Joseph_rings_1(m,n)+1;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.Joseph_rings(6,7)<<endl;
    cout<<te.Joseph_rings_2(6,7)<<endl;
    return 0;
}

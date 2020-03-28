/*********************************************
*     ------------------------
*     ------------------------
*     file name: 264.cpp
*     author   : @ JY
*     date     : 2019--09--27
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
/*找出第n个丑数丑数就是只包含质因数235 的正整数*/
using  namespace  std;
class Solutio{
     public:
         int nthUglyNumber(int n){
             vector<long int> memo(n, INT_MAX);
             memo[0] = 1;
             for(int i=1; i<n; i++){
                 int tmp = memo[i-1];
                 for(int j=0; j<i; j++){
                     if(memo[j]*2 > tmp){
                         memo[i] = min(memo[i], memo[j]*2);
                     }
                     if(memo[j]*3 > tmp){
                         memo[i] = min(memo[i], memo[j]*3);
                     }
                     if(memo[j]*5 > tmp){
                         memo[i] = min(memo[i], memo[j]*5);
                     }
                 }
             }
             return memo[n-1];
         }
};

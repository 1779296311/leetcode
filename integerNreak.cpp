/********************************************* 
*     ------------------------
*     ------------------------
*     file name: integerNreak.cpp
*     author   : @ JY    
*     data     : 2019--09--09
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int integerBreak(int n){
            vector<int> memo(n + 1, -1);

            memo[0] = 0;
            memo[1] = 1;
            for(int i=2; i<=n; i++){
                for(int j=0; j<i; j++){
                    memo[i] = max3(memo[i], (i - j)*j, j*memo[i-j]);
                }
            }
            return memo[n];
        }
        int integerBreak(int n){
            if(n == 2 || n == 3){
                return 2;
            }
            if(n == 4){
                return 4;
            }
            n = n - 5;
            return (int)pow(3, (n / 3 + 1)) * (n % 3 + 2);
        }

    private:
        int max3(int x, int y, int z){
            return max(max(x,y),z);
        }
};

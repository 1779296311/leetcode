/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ60.cpp
*     author   : @ JY
*     date     : 2020--05--21
**********************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
class Solution {
public:
    ::std::vector<double> twoSum(int n){
        ::std::vector<::std::vector<double>>dp(n+1,::std::vector<double>(6*n+1,0));
        for(int i=1; i<=n; ++i){
            for(int j=i; j<=6*i; ++j){
                if(i==1){
                    dp[i][j] = 1;
                    continue;
                }
                for(int k=1; k<=6; ++k){
                    if(j-k>=i-1) dp[i][j] += dp[i-1][j-k];
                }
            }
        }
        ::std::vector<double>res;
        for(int i=n; i<=n*6; ++i){
            res.push_back(dp[n][i]*::std::pow(1.0/6,n));
        }
        return res;
    }
    ::std::vector<double> twoSumBetter(int n){
        ::std::vector<double> dp(n*6+1,0);
        for(int i=1; i<=6; ++i){
            dp[i] = 1;
        }
        for(int i=2; i<=n; ++i){
            for(int j=i*6; j>=i; --j){
                dp[j] = 0;
                for(int k=1; k<=6; ++k){
                    if(j-k>=i-1){
                        dp[j] = dp[j] + dp[j-k];
                    }
                }
            }
        }
        ::std::vector<double>res;
        for(int i=n; i<=n*6; ++i){
            res.push_back(dp[i]*::std::pow(1.0/6,n));
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    te.twoSumBetter(2);
    te.twoSum(2);
    return 0;
}

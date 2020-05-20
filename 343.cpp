/*********************************************
*     ------------------------
*     ------------------------
*     file name: 343.cpp
*     author   : @ JY
*     date     : 2020--05--08
**********************************************/
#include <vector>
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int cuttingRope(int n) {
        if(n<=3){
            return n-1;
        }
        return partition(n);
    }
    int partition(int n){
        if(n<=4){
            return n;
        }
        int res = n;
        for(int i=1; i<=n/2; ++i){
            res = max(res,partition(i)*partition(n-i));
        }
        return res;
    }
    int cuttingRopeDp(int n){
        if(n<=3){
            return --n;
        }
        vector<long long> dp(n+1,0);
        dp[1]   = 1;
        dp[2]   = 2;
        dp[3]   = 3;
        long long res = -1;
        for(int i=4; i<=n; ++i){
            for(int j=1; j<=i/2; ++j){
                dp[i] = max(dp[i],dp[j]*dp[i-j]);
            }
            res = max(res,dp[i]);
        }
        return (int)res;
    }
    int cuttingRopeTx(int n){
        if(n <= 3) return n-1;
        long res = 1;
        while (n > 4) {
            //3最优
            res *= 3;
            res %= 1000000007;
            n -= 3;
        }
        return (res * n) % 1000000007;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    int i = 60;
    cout<<te.cuttingRopeDp(i)<<endl;
    //while(1){
        //int k = te.cuttingRopeDp(i++);
        //cout<<k<<endl;
        //if(k>(1000000007/4)){
            //break;
        //}
    //}
    cout<<i<<endl;
    return 0;
}

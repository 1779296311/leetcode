/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_share_pro.cpp
*     author   : @ JY
*     date     : 2020--06--25
**********************************************/
#include <iostream>
#include <climits>
#include <vector>
#include <stdlib.h>
class Solution{
    public:
//k == 1
        int max_profit_1(::std::vector<int>& prices){
            int size = prices.size();
            if(size<=1)return 0;
            int i_0  = 0;
            int i_1  = -prices[0];
            for(int i=1; i<size; ++i){
                i_0 = ::std::max(i_0, i_1 + prices[i]);
                i_1 = ::std::max(i_1, 0   - prices[i]);
            }
            return i_0;
        }
//k == INT_MAX
        int max_profit_6(::std::vector<int>& prices){
            int size = prices.size();
            if(size<=1)return 0;
            int i_0 = 0;
            int i_1 = -prices[0];
            for(int i=1; i<size; ++i){
                int tmp = i_0;
                i_0 = ::std::max(i_0, i_1 + prices[i]);
                i_1 = ::std::max(i_1, tmp - prices[i]);
            }
            return i_0;
        }
//每sell之后要等一天才能继续交易。只要把这个特点融入上一题的状态转移方程即可：
//dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
//dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])
        int max_profit_2(::std::vector<int>& prices){
            int size  = prices.size();
            if(size<=1)return 0;
            int i_0   = 0;
            int i_1   = -prices[0];
            int i_pre = 0;
            for(int i=1; i<size; ++i){
                int tmp = i_0;
                i_0 = ::std::max(i_0, i_1   + prices[i]);
                i_1 = ::std::max(i_1, i_pre - prices[i]);
                i_pre = tmp;
            }
            return i_0;
        }
//每次交易要支付手续费
        int max_profit_3(::std::vector<int>& prices, int fee){
            int size = prices.size();
            if(size<=1)return 0;
            int i_0 = 0;
            int i_1 = -prices[0];
            for(int i=0; i<size; ++i){
                int tmp = i_0;
                i_0 = ::std::max(i_0, i_1 + prices[i] - fee);
                i_1 = ::std::max(i_1, tmp - prices[i]);
            }
            return i_0;
        }
//k==any
#define ve   ::std::vector<int>
#define vve  ::std::vector<ve> 
#define vvve ::std::vector<vve> 
        int max_profit_4(::std::vector<int>& prices, int k){
            int size = prices.size();
            if(size<=1)return 0;
            if(k>size>>1)return max_profit_1(prices);
            vvve dp = vvve(size, vve(k+1,ve(2,0)));
            for(int i=0; i<=k; ++i)dp[0][i][1]   = -prices[0];
            for(int i=1; i<size; ++i){
                for(int j=1; j<=k; ++j){
                    dp[i][j][0] = ::std::max(dp[i-1][j][0], dp[i-1][j][1]   + prices[i]);
                    dp[i][j][1] = ::std::max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i]);
                }
            }
            return dp[size-1][k][0];
        }
//k==2
        int max_profit_5(::std::vector<int>& prices){
            int size = prices.size();
            if(size<=1)return 0;
            int i_10 = 0;
            int i_20 = 0;
            int i_11 = -prices[0];
            int i_21 = -prices[0];
            for(int i=1; i<size; ++i){
                i_11 = ::std::max(i_11, 0    - prices[i]);
                i_10 = ::std::max(i_10, i_11 + prices[i]);
                i_21 = ::std::max(i_21, i_10 - prices[i]);
                i_20 = ::std::max(i_20, i_21 + prices[i]);
            }
            return i_20;
        }
};

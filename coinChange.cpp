/*********************************************
*     file name: change.cpp
*     author   : @ JY
*     data     : 2019--09--09
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
#include <algorithm>
using  namespace  std;

class Solution{
    public:
        int change(int amount, vector<int> &coins){
            vector<int> memo(amount+1,INT_MAX);
            memo[0]   = 0;
            for(int coin : coins){
                for(int i= 1; i<=amount; i++){
                    if(i>=coin && memo[i - coin] != INT_MAX){
                        memo[i] = min(memo[i - coin]+1, memo[i]);
                    }
                }
            }
            if(memo[amount] == INT_MAX){
                return -1;
            }
            return memo[amount];
        }
        int change_1(int amount, vector<int>& coins){
            vector<int> dp(amount+1,INT_MAX);
            dp[0]    = 0;
            int size = coins.size();
            for(int i=1; i<=amount; ++i){
                for(int j=0; j<size; ++j){
                    if(i>=coins[j] && dp[i-coins[j]] != INT_MAX){
                        dp[i] = min(dp[i],dp[i-coins[j]]+1);
                    }
                }
            }
            return dp[amount]==INT_MAX?-1:dp[amount];
        }
        int changeSum(int amount, vector<int> &coins){
            vector<int> memo(amount+1, 0);
            memo[0] = 1;
            // change for hui you chou fu
            for(int coin : coins){
                for(int i=1; i<=amount; i++){
                    if(i >=coin){
                        memo[i] = memo[i] + memo[i - coin];
                    }
                }
            }
            return memo[amount];
        }
        int changeSum_1(int amount, vector<int> &coins){
            vector<int> memo(amount+1, 0);
            memo[0] = 1;
            for(int i=1; i<=amount; i++){
                for(int coin : coins){
                    if(i >=coin){
                        memo[i] = memo[i] + memo[i - coin];
                    }
                }
            }
            return memo[amount];
        }
        int changeSum_2(int amount, vector<int> &coins){
            vector<int> memo(amount+1, 0);
            memo[0] = 1;
            for(int coin : coins){
                for(int i=amount; i>=coin; --i){
                    memo[i] = memo[i] + memo[i - coin];
                }
            }
            return memo[amount];
        }
};
int main(int argc,const char *argv[]){

    Solution te;
    vector<int> coins = {1,2,3,4,5};
    //cout <<te.change(20,coins)<<endl;
    //cout <<te.change_1(20,coins)<<endl;
    cout <<te.changeSum(7,coins)<<endl;
    cout <<te.changeSum_1(7,coins)<<endl;
    cout <<te.changeSum_2(7,coins)<<endl;
    return 0;
}

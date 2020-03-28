/*********************************************
*     ------------------------
*     ------------------------
*     file name: 91.cpp
*     author   : @ JY
*     data     : 2019--09--13
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
using  namespace  std;

class Solution{
    public:
        int numDecodings(string s){
            int len = s.length();
            if(s[0] == '0'){
                return 0;
            }
            if(len == 0 || len ==1){
                return len;
            }
            vector<int> memo(len+1, 0);
            memo[0] = 1;
            for(int i=1; i<=len; i++){
                int tmp  = s[i-1] - '0';
                if(tmp>0 && tmp<=9){
                    memo[i]   = memo[i]  + memo[i-1];
                }
                if(i>1){
                    int ttt = (s[i-2] - '0')*10  + tmp;
                    if(ttt>9 && ttt<=26){
                            memo[i] = memo[i] + memo[i-2];
                    }
                }
            }
            return memo[len];
        }
        int numDecodings_1(string s){
            int size = s.length();
            if(!size){
                return 0;
            }
            vector<int> dp(++size,0);
            dp[0] = 1;
            for(int i=1; i<size; ++i){
                if(s[i-1]>='0'&&s[i-1]<=9){
                    dp[i] = dp[i] + dp[i-1];
                }
                if(i>1){
                    int t =(s[i-1]-'0')*10+(s[i-1]-'0');
                    if(t>=10 && t<=26){
                        dp[i] = dp[i] + d[i-2];
                    }
                }
            }
            return d[--size];
        }
};

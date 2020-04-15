/*********************************************
*     ------------------------
*     ------------------------
*     file name: 10.cpp
*     author   : @ JY
*     date     : 2019--09--21
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
'.' 匹配任意单个字符'*' 匹配零个或多个前面的那一个元素*/

class Solution{
    public:
        bool isMatch(string s, string t){
            int s_size = s.size();
            int t_size = t.size();

            vector<vector<bool>> memo(s_size+1, vector<bool>(t_size+1, false));
            memo[0][0] = true;
            for(int i=0; i<=s_size; i++){
                for(int j=1; j<=t_size; j++){
                    if(t[j-1] != '*'){
                        if(t[j-1] == s[i-1] || t[j-1] == '.'){
                            memo[i][j] = memo[i-1][j-1];
                        }
                    }else if(t[j-1] == '*'){
                        if(j>1){
                            memo[i][j] = memo[i][j-2];
                        }
                        if(j>1 && i>0){
                            memo[i][j] = memo[i][j] || (memo[i-1][j] && (t[j-2] == '.' || t[j-2] == s[i-1]));
                        }
                    }
                }
            }
            return memo[s_size][t_size];
        }
        bool isMatch_2020(string s, string t){
            int sizeS = s.length();
            int sizeT = t.length();
            vector<vector<bool>> dp(sizeS+1, vector<bool>(sizeT+1,false));
            dp[0][0]  = true;
            for(int i=0; i<=sizeS; ++i){
                for(int j=1; j<=sizeT; ++j){
                    if(t[j-1] == '*' && j>1){
                        //dp[i][j] = dp[i][j-2];//ignore
                        dp[i][j] = dp[i][j-2] || ((i>0)?(dp[i-1][j]&&(t[j-2]=='.'||t[j-2]==s[i-1])):0);
                    }else if(i>0 && (t[j-1]=='.'||t[j-1]==s[i-1])){
                        dp[i][j] = dp[i-1][j-1];
                    }
                }
            }
            return dp[sizeS][sizeT];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string s = "mississppi";
    string t = "mis*is*p*.";
    cout<<te.isMatch_2020(s,t)<<endl;
    return 0;
}

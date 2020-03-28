/*********************************************
*     ------------------------
*     file name: 44.cpp
*     author   : @ JY
*     date     : 2019--09--21
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
'?' 可以匹配任何单个字符'*' 可以匹配任意字符串（包括空字符串）*/ 
class Solution{
    public:
        int isMatch(string s, string t){
            int s_size = s.size();
            int t_size = t.size();
            vector<vector<bool>> memo(s_size+1, vector<bool>(t_size+1, false));
            memo[0][0] = true;
            for(int i=0; i<=s_size; i++){
                for(int j=1; j<=t_size; j++){
                    if(i>0 && t[j-1] != '*'){
                        if(t[j-1] == '?' || t[j-1] == s[i-1]){
                            memo[i][j] = memo[i-1][j-1];
                        }
                    }else if(t[j-1] == '*'){
                        memo[i][j] = memo[i][j-1];
                        if(i>0){ 
                            memo[i][j] = memo[i][j] || memo[i-1][j];
                        }
                    }
                }
            }
            return memo[s_size][t_size];
        }
};

/*********************************************
*     ------------------------
*     file name: 115.cpp
*     author   : @ JY
*     date     : 2019--09--20
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
/*
给定一个字符串 S 和一个字符串 T，计算在 S 的子序列中 T 出现的个数。
一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）
输入: S = "rabbbit", T = "rabbit"
输出: 3*/
class Solution{
    public:
        int numDistinct(string s, string t){
            int s_size = s.size();
            int t_size = t.size();
            vector<vector<int>> memo(s_size+1, vector<int>(t_size+1));
            for(int i=0; i<=s_size; i++){
                for(int j=0; j<=t_size; j++){
                    if(j == 0){
                        memo[i][j] = 1;
                        continue;
                    }
                    if(i == 0){
                        memo[i][j] = 0;
                        continue;
                    }
                    memo[i][j] = memo[i-1][j];
                    if(s[i-1] == t[j-1]){
                        memo[i][j] = memo[i][j] + memo[i-1][j-1];
                    }
                }
            }/*   r   a   b   i   t  */
            /*1-- 0-- 0-- 0-- 0-- 0--
            r 1-- 1-- 0-- 0-- 0-- 0--
            a 1-- 1-- 1-- 0-- 0-- 0--
            b 1-- 1-- 1-- 1-- 0-- 0--
            b 1-- 1-- 1-- 2-- 0-- 0--
            b 1-- 1-- 1-- 3-- 0-- 0--
            i 1-- 1-- 1-- 3-- 3-- 0--
            t 1-- 1-- 1-- 3-- 3-- 3--*/
            return memo[s_size][t_size];
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string s= "rabbbit";
    string t= "rabit";
    cout <<te.numDistinct(s, t)<<endl;
    return 0;
}

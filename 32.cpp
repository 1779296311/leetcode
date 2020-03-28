/*********************************************
*     ------------------------
*     ------------------------
*     file name: 32.cpp
*     author   : @ JY
*     date     : 2019--09--23
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
/*给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。*/
class Solution{
    public:
        int longestValidPraentheses(string s){
            int size = s.size();
            int MAX  = 0;
            vector<int> memo(size, 0);
            for(int i=1; i<size; i++){
                if(s[i] == ')'){
                    if(s[i-1] == '('){
                        memo[i] = (i>1) ? memo[i-2]+2 : 2;
                    }else if(i-memo[i-1]>0 && s[i-memo[i-1]-1] == '('){
                        memo[i] = memo[i-1] + ((i-memo[i-1] > 1) ? (memo[i - memo[i-1] - 2]): 0) + 2;
                }
                MAX = max(memo[i], MAX);
            }
            return MAX;
        }
};

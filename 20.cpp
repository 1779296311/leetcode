/*********************************************
*     ------------------------
*     ------------------------
*     file name: 20.cpp
*     author   : @ JY
*     date     : 2019--09--21
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stack>
using  namespace  std;
/*给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。*/

class Solution{
    public:
        bool isValid(string s){
            int size = s.size();
            if((size & 1) == 1){
                return false;
            }
            stack<char> memo;
            for(int i=0; i<size; i++){
                if(memo.empty && (s[i] == ']' || s[i] == ')' || s[i] == '}')){
                    return false;
                }
                if(s[i] == ']' ||  s[i] == ')' || s[i] == '}'){
                    if(s[i] - memo.top() == 1 || s[i] - memo.top() == 2){
                        memo.pop();
                    }
                }else{
                    memo.push(s[i]);
                }
            }
            return memo.empty();
        }
};

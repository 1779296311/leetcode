/*********************************************
*     ------------------------
*     ------------------------
*     file name: 125.cpp
*     author   : @ JY
*     date     : 2019--09--25
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        bool isPalindrome(string s){
            if(! s.size()){ 
                return true;
            }
            vector<int> memo;
            int size = s.size();
            for(int i=0; i<size; i++){
                if(tolower(s[i])>='a'&&tolower(s[i])<='z'){
                    memo.push_back(tolower(s[i]));
                }else if(s[i] >= '0' && s[i] <='9'){
                    memo.push_back(s[i]);
                }
            }
            int r = memo.size() - 1;
            int l = 0;
            while(r>l){
                if(memo[l] != memo[r]){
                    return false;
                }
                r--;
                l++;
            }
            return true;
     }
};

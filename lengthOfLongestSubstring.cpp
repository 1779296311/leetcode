/********************************************* 
*     ------------------------
*     ------------------------
*     file name: lengthOfLongestSubstring.cpp
*     author   : @JY    
*     data     : 2019--09--04
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
using  namespace  std;"

class Solution{
    public:
        
        int maxLen(string s){
            int size = s.size(), j=0, max =0;
                for(int i=0; i<size; i++){
                    for(int k = j; k<i; k++){
                        if(s[k] == s[i]){
                            j = k+1;
                            break;
                        }
                    }
                    if(max < i-j+1){
                        max = i-j+1;
                    }
                }
            return max;
        }

        int Maxlen(string s){
            int num[256] = {0};
            int max      = 0;
            for(int i=0; i<s.size(); i++){
                if(num[s[i]] !=0 && num[s[i]] >=left){
                    left = num[s[i]];
                }else{
                    max  = max>i-left+1 ? max : i-left+1;
                }
                num[si[i]] = i+1;
            }
            return max;
        }
};

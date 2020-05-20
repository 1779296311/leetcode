/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ50.cpp
*     author   : @ JY
*     date     : 2020--05--18
**********************************************/
#include <iostream>
#include <bitset>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    char firstUniqChar(string s) {
        int left  = 0;
        int right = 1;
        bitset<256> bit;
        while(left<s.length()){
            while(!bit[s[left]] && right<s.length() && s[left]!=s[right++]){}
            if((left==s.length()-1 && !bit[s[left]])||(s[left] != s[right-1] && right==s.length())){
                return s[left];
            }
            bit[s[left++]] = 1;
            right          = left+1;
        }
        return right==1&&s.length()>=1?s[0]:' ';
    }
    char firstUniqChar1(string s){
        int L = 0;
        int R = s.length();
        while(L<R){
            if(L+1 == s[L]){
                ++L;
            }else if(s[L]<=R && s[L]>L && s[s[L]-1] != L){
                swap(s,L,s[L]-1);
            }else{
                s[L] = s[R--];
            }
        }
        return L+1+'a';
    }
    void swap(string& s, int a, int b){
        if(s[a] == s[b]){
            return;
        }
        char t = s[a];
        s[a]   = s[b];
        s[b]   = t;
    }
};
//"aab"
//"aaasdasdahzxnkmnlsnldaad"

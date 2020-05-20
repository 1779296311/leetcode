/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ48.cpp
*     author   : @ JY
*     date     : 2020--05--18
**********************************************/
#include <iostream>
#include <bitset>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int left  = 0;
        int right = 0;
        int res   = 0;
        bitset<256> bit;
        while(right<s.length()){
            while(right<s.length() && bit[s[right]]==0){bit[s[right]]=1;++right;}
            res = max(right-left,res);
            bit[s[left++]] = 0;
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    string s = "p";
    cout<<te.lengthOfLongestSubstring(s)<<endl;
    return 0;
}

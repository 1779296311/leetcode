/*********************************************
*     ------------------------
*     ------------------------
*     file name: 455.cpp
*     author   : @ JY
*     date     : 2020--03--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int gsize = g.size();
        int ssize = s.size();
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int __res = 0;
        int ss    = 0;
        int gs    = 0;
        while(gs<gsize &&ss<ssize){
            if(g[gs] <= s[ss]){
                ++__res;
                ++gs;
            }
            ++ss;
        }
        return __res;
    }
};

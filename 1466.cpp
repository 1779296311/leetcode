/*********************************************
*     ------------------------
*     ------------------------
*     file name: 1466.cpp
*     author   : @ JY
*     date     : 2020--06--02
**********************************************/
#include <vector>
#include <iostream>
#include <stdlib.h>
class Solution {
public:
    ::std::vector<::std::vector<::std::pair<int,int>>> M;
    int minReorder(int n, ::std::vector<::std::vector<int>>& c) {
        M = ::std::vector<::std::vector<::std::pair<int,int>>>(n);
        for(auto v :  c){
            M[v[0]].push_back(::std::make_pair(v[1],1));
            M[v[1]].push_back(::std::make_pair(v[0],0));
        }
        return dfs(0,-1);
    }
    int dfs(int c, int before){
        int res = 0;
        for(auto v : M[c]){
            if(v.first==before)continue;
            res += dfs(v.first,c) + v.second;
        }
        return res;
    }
};

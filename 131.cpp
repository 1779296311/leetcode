/*********************************************
*     ------------------------
*     ------------------------
*     file name: 131.cpp
*     author   : @ JY
*     date     : 2020--10--01
**********************************************/
#include <iostream>
#include <functional>
#include <stdlib.h>
#include <vector>

class Solution{
    public:
        std::vector<std::vector<std::string>> partition(std::string &s){
            std::function<bool(int, int)> _is_p = [&](int i, int j){
                for (; i < j; i++, j--) {
                    if (s[i] != s[j]) {
                        return false;
                    }
                }
                return true;
            };
            int size = s.size();
            std::vector<std::vector<std::string>> res;
            std::function<void(std::vector<std::string> &, int)> _dfs
                = [&](std::vector<std::string> &ans, int i){
                    if(i>=size){
                        res.push_back(ans);
                        return;
                    }
                    for(int j=i; j<size; ++j){
                        if(!_is_p(i, j))continue;
                        ans.push_back(s.substr(i, j-i+1));
                        _dfs(ans, j+1);
                        ans.pop_back();
                    }
                };
            std::vector<std::string> ans;
            _dfs(ans, 0);
            return res;
        }
};

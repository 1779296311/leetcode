/*********************************************
*     ------------------------
*     ------------------------
*     file name: 14.cpp
*     author   : @ JY
*     date     : 2019--09--21
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int size     = strs.size();
        int _size    = INT_MAX;
        string   res = "";
        if(size == 0){
            return res;
        }

        for(int i=0; i<size; i++){
            _size = _size < strs[i].size() ? _size : strs[i].size();
        }
        for(int i=0; i<_size; i++){
            char tmp = strs[0][i];
            for(int j=0; j<size; j++){
                if(strs[j][i] == tmp){
                    continue;
                }else{
                    return res;
                }
            }
            res = res + tmp;
        }
        return res;
    }
};

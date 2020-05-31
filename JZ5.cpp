/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ5.cpp
*     author   : @ JY
*     date     : 2020--05--23
**********************************************/
#include <iostream>
#include <stdlib.h>
class Solution {
public:
    ::std::string replaceSpace(::std::string s) {
        ::std::string res = "";
        int i = 0;
        while(i<s.length()){
            if(s[i]==' '){
                res = res + "%20";
            }else{
                res = res + s[i];
            }
            ++i;
        }
        return res;
    }
};

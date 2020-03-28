/*********************************************
*     ------------------------
*     ------------------------
*     file name: 392.cpp
*     author   : @ JY
*     date     : 2019--09--27
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        bool isSubsequence(string s, string t){
            char *t1 = s.c_str();
            char *s1 = t.c_str();
            while(*s1){
                if(*s1 == *t1){
                    t1++;
                }
                s1++;
                if(*t1 == '\n'){
                    return true;
                }
            }
            return false;
        }
};

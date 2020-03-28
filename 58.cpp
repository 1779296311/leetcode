/*********************************************
*     ------------------------
*     ------------------------
*     file name: 58.cpp
*     author   : @ JY
*     date     : 2019--09--25
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solutio{
    public:
        int lengthOfLast(string s){
            if(!s.size()){
                return 0;
            }
            int size = s.size();
            string::reverse_iterator end_p   = s.rbegin();
            string::reverse_iterator begin_p = s.rend();
            while(*(end_p) == ' ' ){
                end_p++;
            }
            int res = 0;
            while(end_p != begin_p && *(end_p) != ' '){
                res++;
            }
            return res;
        }
};

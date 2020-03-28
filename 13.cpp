/*********************************************
*     ------------------------
*     ------------------------
*     file name: 13.cpp
*     author   : @ JY
*     date     : 2019--10--13
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
using  namespace  std;
class Solution{
    public:
        int romanToInt(string s){
            map<char,int> roman = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100},{'D', 500}, {'M', 1000}};
            int size = s.size();
            int res  = 0;
            for(int i=0; i<size; i++){
                int tmp = 0;
                if(roman[s[i]] >= roman[s[i+1]]){
                    tmp = roman[s[i]];
                }else{
                    tmp = roman[s[i+1]] - roman[s[i]];
                    i++;
                }
                res = res + tmp;
            }
            return res;
         }
};

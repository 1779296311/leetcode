/*********************************************
*     ------------------------
*     ------------------------
*     file name: 17.cpp
*     author   : @ JY
*     date     : 2019--10--19
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <map>
using  namespace  std;
class Solution{
    public:
        vector<string> letterCombinations(string digits){
            vector<string> res;
            if(!digits.size()){
                return res;
            }
            int size = digits.size();
            map<char, vector<char>> hs = {
                {'2',{'a','b','c'    }},
                {'3',{'d','e','f'    }},
                {'4',{'g','h','i'    }},
                {'5',{'j','k','l'    }},
                {'6',{'m','n','o'    }},
                {'7',{'p','q','r','s'}},
                {'8',{'t','u','v'    }},
                {'9',{'w','x','y','z'}},
            };
        }
};







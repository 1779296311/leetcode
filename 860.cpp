/*********************************************
*     ------------------------
*     ------------------------
*     file name: 860.cpp
*     author   : @ JY
*     date     : 2020--03--16
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0;
        int ten  = 0;
        for(int i=0; i<bills.size(); ++i){
            if(bills[i] == 5){
                ++five;
            }else if(bills[i] == 10){
                if(!five){
                    return false;
                }
                ++ten;
                --five;
            }else{
                int tmp = 15;
                if(ten){
                    --ten;
                    tmp = 5;
                }
                while(tmp>0 && five>0){
                    --five;
                    tmp = tmp - 5;
                }
                if(tmp){
                    return false;
                }
            }
        }
        return true;
    }
};

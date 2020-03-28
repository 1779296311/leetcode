/*********************************************
*     ------------------------
*     ------------------------
*     file name: 122.cpp
*     author   : @ JY
*     data     : 2019--09--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Slotion{
    public:
        int maxProfit(vector<int>& prices){ 
            int size = prices.size();
            if(size == 1 || size == 0){
                return 0;
            }
            int maxS = 0;
            for(int i=1; i<size; i++){
                if(prices[i] > prices[i-1]){
                    maxS = maxS + prices[i] - prices[i-1];
                }
            }
            return maxS;
        }
};

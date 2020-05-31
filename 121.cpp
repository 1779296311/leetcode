/*********************************************
*     ------------------------
*     file name: 121.cpp
*     author   : @ JY
*     date     : 2019--09--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <climits>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int maxProfit(vector<int>& prices){
            int size = prices.size();
            int minS = INT_MAX;
            int maxS = 0;
            for(int i=0; i<size; i++){
                minS = min(minS, prices[i]);
                maxS = max(maxS,prices[i]-minS);
            }
            return maxS;
        }
};

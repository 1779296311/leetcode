/*********************************************
*     ------------------------
*     ------------------------
*     file name: 134.cpp
*     author   : @ JY
*     date     : 2020--03--16
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int size = gas.size();
        for(int i=0,j; i<size; i+=j+1){
            int tmp = 0;
            for(j=0; j<size; ++j){
                tmp = tmp + gas[(i+j)%size];
                if(tmp<cost[(i+j)%size]){
                    break;
                }
                tmp = tmp - cost[(i+j)%size];
            }
            if(j==size){
                return i;
            }
        }
        return -1;
    }
};

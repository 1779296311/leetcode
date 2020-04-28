/*********************************************
*     ------------------------
*     ------------------------
*     file name: getMinStop.cpp
*     author   : @ JY
*     date     : 2020--03--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
using  namespace  std;
class Solution{
    private:
    public:
        int getMinStop(int L, int P, vector<int>& gas, vector<int>& cost){
            int size  = gas.size();
            int __res = 0;
            priority_queue<int,vector<int>,greater<int>> q;
            for(int i=0; i<size; ++i){
                while(!q.empty()&&P<(L-cost[i])){
                    P = P + q.top();
                    q.pop();
                    ++__res;
                }
                if(q.empty()&&P<(L-cost[i])){
                    return -1;
                }
                P = P-(L-cost[i]);
                L = cost[i];
                q.push(gas[i]);
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    int l = 25;
    int p = 10;
    vector<int> cost = {15,11,5,4};
    vector<int> gas  = {10,5,2,4};
    cout<<te.getMinStop(l,p,gas,cost)<<endl;
    return 0;
}

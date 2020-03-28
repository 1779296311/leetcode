/*********************************************
*     ------------------------
*     ------------------------
*     file name: splitGold.cpp
*     author   : @ JY
*     date     : 2020--03--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#define poll(q)  \
    ({add = q.top(),q.pop(),add;})
using  namespace  std;
class Solution{
    public:
        int minSplitCost(vector<int>& money){
            priority_queue<int,vector<int>,greater<int>> q(money.begin(),money.end());
            int __res = 0;
            while(q.size()>1){
                //int a = q.top();
                //q.pop();
                //int b = q.top();
                //q.pop();
                //__res = __res + a + b;
                int add = poll(q) + poll(q);
                q.push(({__res+=add,add;}));
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> money = {10,20,30};
    cout<<te.minSplitCost(money)<<endl;
    return 0;
}

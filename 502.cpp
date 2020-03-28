/*********************************************
*     ------------------------
*     ------------------------
*     file name: 502.cpp
*     author   : @ JY
*     date     : 2020--03--14
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <queue>
using  namespace  std;
class Solution {
    private:
        struct Node{
            int p;
            int c;
            Node(int pp, int cc): p(pp),c(cc){}
        };
        struct mless{
            bool operator()(Node &a, Node &b){
                return a.p<b.p;
            }
        };
        struct mgreater{
            bool operator()(Node &a, Node &b){
                return a.c>b.c;
            }
        };
    private:
        priority_queue<Node,vector<Node>,mgreater>   small;
        priority_queue<Node,vector<Node>,mless>      big;
    public:
        int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
            for(int i=0; i<Profits.size(); ++i){
                small.push(Node(Profits[i],Capital[i]));
            }
            for(int i=0; i<k; ++i){
                while(!small.empty()&&small.top().c<=W){
                    big.push(small.top());
                    small.pop();
                }
                if(big.empty()){
                    return W;
                }
                W += big.top().p;
                big.pop();
            }
            return W;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int>p = {1,2,3,5,2,5,1};
    vector<int>c = {0,1,1,3,3,1,2};
    cout<<te.findMaximizedCapital(4,5,p,c)<<endl;
    return 0;
}

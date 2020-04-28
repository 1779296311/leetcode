/*********************************************
*     ------------------------
*     ------------------------
*     file name: TY.cpp
*     author   : @ JY
*     date     : 2020--04--21
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int isTY(string a, string b){
            int sizeA = a.length();
            int sizeB = b.length();
            if(sizeA > sizeB){
                return -1;
            }
            int flag = 0;
            vector<int> cost(256,0);
            for(int i=0; i<sizeA; ++i){
                ++cost[a[i]];
            }
            for(int i=0; i<sizeA; ++i){
                if(cost[b[i]]-- <= 0){
                    ++flag;
                }
            }
            for(int i=sizeA; i<sizeB; ++i){
                if(!flag){
                    return i-sizeA;
                }
                if(cost[b[i]]-- <= 0){
                    ++flag;
                }
                if(++cost[b[i-sizeA]] <= 0){
                    --flag;
                }
            }
            return !flag?sizeB-sizeA:-1;
        }
        int minTY(string a, string b){
            int sizeA = a.length();
            int sizeB = b.length();
            if(sizeA > sizeB){
                return -1;
            }
            vector<int> cost(256,0);
            for(int i=0; i<sizeA; ++i){
                ++cost[a[i]];
            }
            int all   = sizeA;
            int res   = sizeB;
            int left  = 0;
            int right = 0;
            while(right<sizeB){
                if(--cost[b[right++]] >=0){
                    --all;
                }
                if(!all){
                    while(++cost[b[left++]]<=0){}//++cost[b[left++]];
                    ++all;
                    res = min(res,right-left+1);
                    //++cost[b[left++]];
                }
            }
            return res==sizeB+1?-1:res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    string a = "gghghb";
    string b = "asgghhhhhghbdbzh";
    //string b = "asdzxbncghhhhhhhhghbgjaaa";
    //cout<<te.isTY(a,b)<<endl;
    cout<<te.minTY(a,b)<<endl;
    return 0;
}

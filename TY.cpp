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
        // da xiao xiang tong
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
        int isTY2(string a, string b){
            int sizeA = a.length();
            int sizeB = b.length();
            vector<int> cost(256,0);
            int lessN = sizeA;
            for(int i=0; i<sizeA; ++i){
                ++cost[a[i]];
            }
            for(int i=0; i<sizeA; ++i){
                if(--cost[b[i]] >= 0){
                    --lessN;
                }
            }
            for(int i=sizeA; i<sizeB; ++i){
                if(!lessN){
                    return i-sizeA;
                }
                if(--cost[b[i]] >=0){
                    --lessN;
                }
                if(++cost[b[i-sizeA]] >0){
                    ++lessN;
                }
            }
            return !lessN?sizeB-sizeA:-1;
        }
        ///-------------------------------------------------------------------------
        //daxiao bu tong
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
            int res   = sizeB+1;
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
    string a3 = "gghghb";
    string b3 = "gghghb";
    string a4 = "gghghb";
    string b4 = "asgghgghghbhhhhghbdbzh";
    string a1 = "gghghb";
    string b1 = "asgghhhhhghbdbzh";
    string a2 = "gghgghhhhhghbdbzhghb";
    string b2 = "asgghhhhhghbdbzh";
    string a  = "gghghb";
    string b  = "asgghhhhhghbdbzh";
    cout<<te.isTY(a,b)<<endl;
    cout<<te.isTY2(a,b)<<endl;
    cout<<"----------------------------"<<endl;
    cout<<te.isTY(a1,b1)<<endl;
    cout<<te.isTY2(a1,b1)<<endl;
    cout<<"----------------------------"<<endl;
    cout<<te.isTY(a3,b3)<<endl;
    cout<<te.isTY2(a3,b3)<<endl;
    cout<<"----------------------------"<<endl;
    cout<<te.isTY(a2,b2)<<endl;
    cout<<te.isTY2(a2,b2)<<endl;
    cout<<"----------------------------"<<endl;
    cout<<te.isTY(a4,b4)<<endl;
    cout<<te.isTY2(a4,b4)<<endl;
    cout<<"----------------------------"<<endl;
    //string b = "asdzxbncghhhhhhhhghbgjaaa";
    //cout<<te.isTY(a,b)<<endl;
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 60.cpp
*     author   : @ JY
*     date     : 2020--05--07
**********************************************/
#include <iostream>
#include <algorithm>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
    string getPermutation(int n, int k){
        string ori = "123456789";
        ori        = ori.substr(0,n);
        int JN = 1;
        for(int i=1; i<n; ++i){
            JN = JN * i;
        }
        string res = "";
        int p      = 0;
        int rest   = k;
        for(int i=n-1; i>=0&&rest; --i){
            p    = rest/JN;
            if(!(rest%JN)){
                res = res + ori[p-1];
                ori.erase(p-1,1);
                reverse(ori.begin(),ori.end());
                return res+ori;
            }
            res  = res + ori[p];
            rest = rest - p*JN;
            JN   = JN/i;
            ori.erase(p,1);
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.getPermutation(3,3)<<endl;
    //cout<<te.getPermutation(4,6)<<endl;
    //cout<<te.getPermutation(4,7)<<endl;
    //cout<<te.getPermutation(4,8)<<endl;
    //cout<<te.getPermutation(4,9)<<endl;
    //cout<<te.getPermutation(4,10)<<endl;
    return 0;
}

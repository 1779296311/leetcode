/*********************************************
*     ------------------------
*     ------------------------
*     file name: 76.cpp
*     author   : @ JY
*     date     : 2020--05--03
**********************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
    string minWindow(string a, string b) {
        int sizea = a.length();
        int sizeb = b.length();
        if(sizeb>sizea){
            return "";
        }
        vector<int>cost(256,0);
        for(int i=0; i<sizeb; ++i){
            cost[b[i]]++;
        }
        int all   = sizeb;
        int res   = INT_MAX;
        int begin = 0;
        int L     = 0;
        int R     = 0;
        while(R<sizea){
            if(--cost[a[R++]] >=0){
                --all;
            }
            if(!all){
                while(++cost[a[L++]]<=0){}
                all = 1;
                if(res > R-L+1){
                    res   = R-L+1;
                    begin = L;
                }
            }
        }
        return res==INT_MAX?"":a.substr(!begin?0:begin-1,res);
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    //string a = "BNAC";
    //string b = "ABC";
    string a = "aaa";
    string b = "aaa";
    cout<<te.minWindow(a,b)<<endl;
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 402.cpp
*     author   : @ JY
*     date     : 2020--03--15
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using  namespace  std;
class Solution {
public:
    string removeKdigits(string num, int k) {
        int size     = num.size();
        int i        = 0;
        string __res = "";
        vector<char> s;
        while(k>0&&i<size){
            while(k>0&&s.size()&&s[s.size()-1]>num[i]){
                s.pop_back();
                --k;
            }
            if(!(num[i]=='0'&&s.empty())){
                s.push_back(num[i]);
            }
            ++i;
        }
        while(!s.empty()&&k>0){
            s.pop_back();
            --k;
        }
        for(int i=0; i<s.size(); ++i){
           __res.append(1,s[i]);
        }
        __res.append(num,i,(size-i+1));
        return __res==""?"0":__res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    cout<<te.removeKdigits("10200",1)<<endl;
    cout<<te.removeKdigits("1432219",3)<<endl;
    cout<<te.removeKdigits("10",1)<<endl;
    cout<<te.removeKdigits("9999999999",7)<<endl;
    cout<<te.removeKdigits("",3)<<endl;
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ38.cpp
*     author   : @ JY
*     date     : 2020--05--13
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
public:
    vector<string> permutation(string s) {
         vector<string> res = partition(s);
         sort(res.begin(),res.end());
         res.erase(unique(res.begin(), res.end()), res.end());
         return res;
    }
    vector<string> partition(string s){
        if(s.length() == 1){
            return vector<string>{s};
        }
        vector<string> res;
        for(int i=0; i<s.length(); ++i){
            char tmp = s[i];
            string e(s.begin(),s.end());
            e.erase(i,1);
            vector<string>t = partition(e);
            for(int j=0; j<t.size(); ++j){
                t[j].insert(0,1,tmp);
                res.push_back(t[j]);
            }
        }
        return res;
    }
    void debug(vector<string>& s){
        for(int i=0; i<s.size(); ++i){
            cout<<s[i]<<" ";
        }
        cout<<endl;
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    string s = "aaabc";
    vector<string> res = te.permutation(s);
    te.debug(res);
    return 0;
}

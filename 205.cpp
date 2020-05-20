/*********************************************
*     ------------------------
*     ------------------------
*     file name: 205.cpp
*     author   : @ JY
*     date     : 2020--05--02
**********************************************/
#include <iostream>
#include <unordered_map>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char,int> mp1;
        unordered_map<char,int> mp2;
        int i = 0;
        while(i<s.length()){
            auto f1 = mp1.find(s[i]);
            auto f2 = mp2.find(t[i]);
            if(f1 == mp1.end() && f2 == mp2.end()){
                mp1[s[i]] = i;
                mp2[t[i]] = i;
            }else if(f1 != mp1.end() && f2 != mp2.end()){
                if(mp1[s[i]]==mp2[t[i]]){
                    mp1[s[i]] = i;
                    mp2[t[i]] = i;
                }else{
                    return false;
                }
            }else{
                return false;
            }
            ++i;
        }
        return true;
    }
    //void debug(vector<int>& a, vector<int>& b){
        //for(int i=0; i<a.size(); ++i){
            //cout<<a[i]<<"  ";
        //}
        //cout<<endl;
        //for(int i=0; i<b.size(); ++i){
            //cout<<a[i]<<"  ";
        //}
    //}
};
int main(int argc,const char *argv[]){
    Solution te;
    string s = "paper121";
    string t = "title242";
    cout<<te.isIsomorphic(s,t)<<endl;
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ58.cpp
*     author   : @ JY
*     date     : 2020--05--20
**********************************************/
#include <iostream>
#include <stack>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    string reverseWords(string s) {
        stack<string> st;
        int end   = 0;
        int start = 0;
        while(end<s.length()){
            start = end;
            while(start<s.length() && s[start] == ' '){++start;}
            if(start==s.length()){break;}
            end = start;
            while(end<s.length() && s[end] != ' '){++end;}
            st.push(s.substr(start,end-start));
        }
        string res = "";
        while(st.size()>1){
            res = res + st.top()+" ";
            st.pop();
        }
        return res + ((st.size()==1)?(st.top()):(""));
    }
    string reverseLeftWords(string s, int n) {
        return rorate(s,0,n-1,s.length());
    }
    string rorate(string& s, int l, int m, int r){
        if(l>m || l>r || m>=r){
            return s;
        }
        if(m-l == r-m-2){
            return rorateReal(s,l,m+1,m-l+1);
        }else if(m-l > r-m-2){
            return rorate(rorateReal(s,l,m+1,r-m-1),l+r-m-1,m,r);
        }else{
            return rorate(rorateReal(s,l,m+1,m-l+1),m+1,(m<<1)-l+1,r);
        }
    }
    string& rorateReal(string& s, int begin1, int begin2, int n){
        char t;
        while(n-->0){
            t         = s[begin1];
            s[begin1] = s[begin2];
            s[begin2] = t;
            ++begin1;
            ++begin2;
        }
        return s;
    }
};
//"the sky is blue
int main(int argc,const char *argv[]){
    Solution te;
    string s = "lrloseumgh";
    cout<<te.reverseLeftWords(s,6)<<endl;
    return 0;
}

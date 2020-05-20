/*********************************************
*     ------------------------
*     ------------------------
*     file name: calc.cpp
*     author   : @ JY
*     date     : 2020--03--31
**********************************************/
#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int calc(string opera, int& index){
            int nowNum = 0;
            list<string> st;
            while(index < opera.length() && opera[index] != ')'){
                if(opera[index]>='0' && opera[index] <='9'){
                    nowNum = nowNum*10 + opera[index] - '0';
                }else if(opera[index] != '('){
                    addNum(st,nowNum);
                    st.push_back(string(1,opera[index]));
                    nowNum = 0;
                }else{
                    nowNum = calc(opera,++index);
                }
                ++index;
            }
            addNum(st,nowNum);
            return st.empty()?0:getRes(st);
        }
        void addNum(list<string>& st,int n){
            if(!st.empty()){
                string tmp = st.back();
                st.pop_back();
                if(tmp=="-" || tmp=="+"){
                    st.push_back(tmp);
                }else{
                    int t = stoi(st.back());
                    st.pop_back();
                    n = tmp=="*"?t*n:t/n;
                }
            }
            st.push_back(to_string(n));
        }
        int getRes(list<string>& st){
            int __res = 0;
            bool add  = true;
            while(!st.empty()){
                string cur = st.front();
                st.pop_front();
                if(cur == "-"){
                    add = false;
                }else if(cur == "+"){
                    add = true;
                }else{
                    int num = stoi(cur);
                    __res  += add?(num):(-num);
                }
            }
            return __res;
        }
        int calc(string opera){
            int index = 0;
            return calc(opera,index);
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //string op = "2*3";
    //string op = "((3+5)*2+4)/5+6+(4*(2+3))-((3+5)*2+4)/5+6/4*2+3";
    //string op = "-2+2";
    //string op = "2-((-2+2)*5+7+(2*3)-6)*1";
    string op = "(-2+1)";
    cout<<te.calc(op)<<endl;
    //cout<<im<<endl;
    return 0;
}

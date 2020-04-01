/*********************************************
*     ------------------------
*     ------------------------
*     file name: calc.cpp
*     author   : @ JY
*     date     : 2020--03--31
**********************************************/
#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int calc(string opera, int& index){
            int nowNum = 0;
            stack<string> st;
            while(index < opera.length() && opera[index] != ')'){
                if(opera[index]>='0' && opera[index] <='9'){
                    nowNum = nowNum*10 + opera[index] - '0';
                }else if(opera[index] != '('){
                    addNum(st,nowNum);
                    st.push(string(1,opera[index]));
                    nowNum = 0;
                }else{
                    nowNum = calc(opera,++index);
                }
                ++index;
            }
            addNum(st,nowNum);
            return st.empty()?0:getRes(st);
        }
        void addNum(stack<string>& st,int n){
            if(!st.empty() && (st.top()=="*"||st.top()=="/")){
                if(st.top() == "*"){
                    st.pop();
                    n = stoi((st.top()))*n;
                    st.pop();
                    st.push(to_string(n));
                }else if(st.top() == "/"){
                    st.pop();
                    n = stoi((st.top()))/n;
                    st.pop();
                    st.push(to_string(n));
                }
                return;
            }
            st.push(to_string(n));
        }
        int getRes(stack<string>& st){
            int __res = stoi(st.top());
            st.pop();
            while(!st.empty()){
                if(st.top() == "-"){
                    st.pop();
                    __res = stoi(st.top()) - __res;
                    st.pop();
                }else if(st.top() == "+"){
                    st.pop();
                    __res = stoi(st.top()) + __res;
                    st.pop();
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
    string op = "((3+5)*2+4)/5+6+(4*(2+3))-((3+5)*2+4)/5+6/4*2+3";
    cout<<te.calc(op)<<endl;
    return 0;
}

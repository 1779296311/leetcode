/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_stack_pro.cpp
*     author   : @ JY
*     date     : 2020--05--03
**********************************************/
#include <iostream>
#include <stack>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int remove_Stack_Last(stack<int>& st){
            int tmp = st.top();
            st.pop();
            if(st.empty()){
                return tmp;
            }else{
                int res = remove_Stack_Last(st);
                st.push(tmp);
                return res;
            }
        }
        void reverse_Stack(stack<int>& st){
            if(st.empty()){
                return;
            }
            int tmp = remove_Stack_Last(st);
            reverse_Stack(st);
            st.push(tmp);
        }
        void debug(){
            stack<int> st;
            st.push(0);
            st.push(1);
            st.push(2);
            st.push(3);
            st.push(4);
            st.push(5);
            //cout<<remove_Stack_Last(st)<<endl;
            reverse_Stack(st);
            while(!st.empty()){
                cout<<st.top()<<" ";
                st.pop();
            }
            cout<<endl;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    te.debug();
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 155.cpp
*     author   : @ JY
*     date     : 2019--09--29
**********************************************/
#include <iostream>
#include <stdlib.h>
using  namespace  std;
class MinStack {
public:
    int *data;
    int top;
    /** initialize your data structure here. */
    MinStack() {
        data = new int[20];
        top  = -1;
    }
    
    void push(int x) {
        data[++top] = x;
    }
    
    void pop() {
        top--;
    }
    
    int Top() {
        return data[top];
    }
    
    int getMin() {
        int res = INT_MAX;
        while(!empty()){
            res = min(res, Top());
            pop();
        }
        return res; 
    }
    bool empty(){
        return top == -1;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

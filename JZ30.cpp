/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ30.cpp
*     author   : @ JY
*     date     : 2020--05--12
**********************************************/
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
using  namespace  std;
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
    }
    void push(int x) {
        nums.push_back(x);
        if(index.empty()){
            index.push(nums.size()-1);
        }else if(nums[index.top()] > x){
            index.push(nums.size()-1);
        }
    }
    void pop(){
        nums.pop_back();
        if(nums.size() == index.top()){
            index.pop();
        }
    }
    int top() {
        return nums[nums.size()-1];
    }
    int min() {
        return nums[index.top()];
    }
private:
    vector<int> nums;
    stack<int> index;
};


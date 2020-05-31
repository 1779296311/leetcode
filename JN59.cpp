/*********************************************
*     ------------------------
*     ------------------------
*     file name: JN59.cpp
*     author   : @ JY
*     date     : 2020--05--21
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <stdlib.h>
class Solution {
public:
    ::std::vector<int> maxSlidingWindow(::std::vector<int>& nums, int k) {
        ::std::vector<int>res;
        ::std::list<int>tmp;
        for(int i=0; i<nums.size(); ++i){
            while(!tmp.empty() && nums[tmp.back()]<nums[i]){tmp.pop_back();}
            tmp.push_back(i);
            if(tmp.front()+k == i){
                tmp.pop_front();
            }
            if(i>=k-1){
                res.push_back(nums[tmp.front()]);
            }
        }
        return res;
    }
};
class MaxQueue {
public:
    MaxQueue():left(0),right(0),index1(0),index2(0){
    }
    int max_value(){
        if(index1 >= values.size())return -1;
        return values[indexs[index2]];
    }
    void push_back(int value){
        values.push_back(value);
        if(values.size() == 0){
            indexs.push_back(0);
        }else{
            while(indexs.size()>index2 && value>values[indexs.back()]){
                indexs.pop_back();
            }
            indexs.push_back(values.size()-1);
        }
    }
    int pop_front(){
        if(index1 >= values.size())return -1;
        if(indexs[index2] == index1){
            ++index2;
        }
        return values[index1++];
    }
private:
    ::std::vector<int>values;
    ::std::vector<int>indexs;
    int left;
    int right;
    int index1;
    int index2;
};


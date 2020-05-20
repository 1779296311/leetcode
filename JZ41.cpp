#include <iostream>
#include <queue>
#include <stdlib.h>
using  namespace  std;
class MedianFinder{
public:
    /** initialize your data structure here. */
    MedianFinder(){
    }
    void addNum(int num){
        if(small.size() == big.size()){
            small.push(num);
            big.push(small.top());
            small.pop();
        }else if(small.size() == big.size()-1){
            big.push(num);
            small.push(big.top());
            big.pop();
        }
    }
    double findMedian(){
        if(small.size() == big.size()){
            return (double)(small.top()+big.top())/2;
        }else if(small.size()>big.size()){
            return small.top();
        }else{
            return big.top();
        }
    }
private:
    priority_queue<int,vector<int>,less<int>> small;
    priority_queue<int,vector<int>,greater<int>> big;
};

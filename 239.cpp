/*********************************************
*     ------------------------
*     ------------------------
*     file name: 239.cpp
*     author   : @ JY
*     date     : 2020--05--03
**********************************************/
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            list<int> post;
            vector<int> res;
            for(int i=0; i<nums.size(); ++i){
                while(!post.empty() && nums[i]>=nums[post.front()]){
                    post.pop_front();
                }
                post.push_front(i);
                if(post.back() == i-k){
                    post.pop_back();
                }
                if(i>=k-1){
                    res.push_back(nums[post.back()]);
                }
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int>nums = {14,6,2,3,6,7,12};
    vector<int>res  = te.maxSlidingWindow(nums,3);
    for(int i=0; i<res.size(); ++i){
        cout<<res[i]<<" ";
    }
    return 0;
}

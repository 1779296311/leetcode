/*********************************************
*     ------------------------
*     ------------------------
*     file name: 45.cpp
*     author   : @ JY
*     date     : 2019--09--23
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
using  namespace  std;
/*给定一个非负整数数组，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。*/
class Solution{
    public:
        int jump(vector<int>& nums){
            int size = nums.size();
            if(size<2){
                return 0;
            }
            int __res = 1;
            int c_max = nums[0];
            int p_max = nums[0];
            //priority_queue<int> q;
            q.push(nums[0]);
            for(int i=1; i<size; ++i){
                if(c_max<i){
                    c_max = p_max;
                    //c_max = q.top();
                    ++__res;
                    //q.pop();
                }
                if(p_max < i+nums[i]){
                    p_max = nums[i]+i;
                }
                //q.push(i+nums[i])
            }
            return __res;
        }
};

int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {2,3,1,1,2};
    cout<<te.jump(nums)<<endl;
    return 0;
}

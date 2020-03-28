/*********************************************
*     ------------------------
*     ------------------------
*     file name: 66.cpp
*     author   : @ JY
*     date     : 2019--10--16
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using  namespace  std;
class Solution{
    public:
        vector<int> plusOne(vector<int>& nums){
            if(!nums.size()){
                return nums;
            }
            vector<int> res;
            int size = nums.size();
            int flag = 0;
            int tmp;
            for(int i=size-1; i>=0; i--){
                if(i == size-1){
                    tmp = nums[i] + 1;
                }else{
                    tmp = nums[i];
                }
                if(tmp+flag >= 10){
                    res.push_back(tmp+flag-10);
                    flag = 1;
                }else{
                    res.push_back(tmp+flag);
                    flag = 0;
                }
            }
            if(flag == 1){
                res.push_back(1);
            }
            reverse(res.begin(),res.end());
            return res;
        }
};
vector<int> plusOne(vector<int>& nums){
    for(int i=nums.size()-1; i>=0; i--){
        if(nums[i] == 9){
            nums[i] = 0;
        }else{
            nums[i]++;
            break;
        }
    }
    if(nums[0] == 0){
        nums.push_back(0);
        nums[0] = 1;
    }
    return nums;
}
int main(int argc,const char *argv[]){
    Solution te;
    //int num[5] = {1,2,3,4,5};
    int num[5] = {9,9,9,9,9};
    vector<int>nums(num,num+5);
    nums = te.plusOne(nums);
    for(auto a : nums){
        cout<<a<<"__";
    }
    return 0;
}

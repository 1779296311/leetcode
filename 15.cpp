/*********************************************
*     ------------------------
*     ------------------------
*     file name: 15.cpp
*     author   : @ JY
*     date     : 2019--10--03
**********************************************/
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        vector<vector<int>> threeSum(vector<int>& nums){
            vector<vector<int>> res;
            if(!nums.size()){
                return res;
            }
            int size = nums.size();
            sort(nums.begin(), nums.end());
            if(size < 3){
                return res;
            }
            for(int left=0; left<size; left++){
                int mid   = left + 1;
                int right = size - 1;
                if(nums[left] > 0){
                    return res;
                }
                if(left > 0 && nums[left] == nums[left-1]){
                    continue;
                }
                while(mid < right){
                    if((nums[left] + nums[mid] + nums[right]) > 0){
                        --right;
                    }else if((nums[left] + nums[mid] + nums[right]) < 0){
                        ++mid;
                    }else{
                        res.push_back({nums[left],nums[mid],nums[right]});
                        while(mid<right && nums[mid++] == nums[mid]);
                        while(mid<right && nums[right--] == nums[right]);
                    }
                }
            }
            return res;
        }
};

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 41.cpp
*     author   : @ JY
*     date     : 2020--04--30
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int firstMissingPositive(vector<int>& nums){
            int l = 0;
            int r = nums.size();
            while(l<r){
                if(nums[l] == l+1){
                    ++l;
                }else if(nums[l]<=r && nums[l]>l && nums[l] != nums[nums[l]-1]){
                    swap(nums,l,nums[l]-1);
                }else{
                    nums[l] = nums[--r];
                }
            }
            return ++l;
        }
        void swap(vector<int>& nums, int a, int b){
            if(nums[a] == nums[b]){
                return;
            }
            nums[a] = nums[a] ^ nums[b];
            nums[b] = nums[a] ^ nums[b];
            nums[a] = nums[a] ^ nums[b];
        }
};

/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ51.cpp
*     author   : @ JY
*     date     : 2020--05--19
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return partition1(nums,0,nums.size()-1);
    }
    int partition1(vector<int>& nums, int l, int r){
        if(l>=r){
            return 0;
        }
        int mid  = l+((r-l)>>1);
        return partition1(nums,l,mid)+partition1(nums,mid+1,r)+merge(nums,l,mid,r);
    }
    int merge(vector<int>& nums, int l, int mid, int r){
        int size = r-l+1;
        int res  = 0;
        vector<int>tmp(size);
        int L = l;
        int R = mid+1;
        int i = 0;
        while(L<=mid && R<=r){
            tmp[i++] = nums[L]>nums[R]?({res+=mid-L+1;nums[R++];}):nums[L++];
        }
        while(R<=r){
            tmp[i++] = nums[R++];
        }
        while(L<=mid){
            tmp[i++] = nums[L++];
        }
        for(int i=0; i<size; ++i){
            nums[i+l] = tmp[i];
        }
        return res;
    }
    void debug(vector<int>& nums){
        for(int i=0; i<nums.size(); ++i){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    vector<int>nums = {7,5,6,4};
    //vector<int>nums = {1,2,3,1,3};
    cout<<te.reversePairs(nums)<<endl;
    te.debug(nums);
    return 0;
}

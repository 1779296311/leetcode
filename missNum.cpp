/*********************************************
*     ------------------------
*     ------------------------
*     file name: missNum.cpp
*     author   : @ JY
*     date     : 2020--04--22
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        int missNum(vector<int>& nums){
            int size = nums.size();
            int l    = 0;
            int r    = size;
            while(l<r){
                cout<<l<<"--"<<r<<endl;
                if(nums[l] == l+1){
                    ++l;
                }else if(nums[l]<=l || nums[l]>r || nums[nums[l]-1] == nums[l]){
                    nums[l] = nums[--r];
                }else{
                    swap(nums,l,nums[l]-1);
                }
            }
            return l+1;
        }
        void swap(vector<int>& nums, int a, int b){
            if(nums[a] == nums[b]){
                return;
            }
            nums[a] = nums[a] ^ nums[b];
            nums[b] = nums[a] ^ nums[b];
            nums[a] = nums[a] ^ nums[b];
        }
        int missNum2(vector<int>& nums){
            int L = 0;
            int R = nums.size();
            while(L < R){
                if(nums[L] == L+1){
                    ++L;
                }else if(nums[L]<=R&&nums[L]>L&&nums[nums[L]-1] != nums[L]){
                    swap(nums,L,nums[L]-1);
                }else{
                    nums[L] = nums[--R];
                }
            }
            return L+1;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //vector<int> nums = {0,1,2,3,4,6,7};
    //vector<int> nums = {-5,3,1,2,5,6};
    vector<int> nums = {2,1};
    cout<<te.missNum2(nums)<<endl;
    return 0;
}

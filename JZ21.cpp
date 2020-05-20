/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ21.cpp
*     author   : @ JY
*     date     : 2020--05--11
**********************************************/
#include <iostream>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    ////------------------quickSort------partition-------------
    vector<int> exchange1(vector<int>& nums){
        int left  = -1;
        int right = nums.size();
        int cur   = 0;
        while(cur<right){
            if(nums[cur]&1){
                swap(nums,++left,cur++);
            }else{
                swap(nums,cur,--right);
            }
        }
        return nums;
    }
    ////------------------normal-------------------
    vector<int> exchange(vector<int>& nums) {
        int size = nums.size();
        int index1 = 0;
        int index2 = 0;
        while(index2<size){
            if(nums[index2]&1){
                ++index2;
            }else{
                index1 = index2++;
                while(index2<size&&!(nums[index2]&1)){
                    ++index2;
                }
                if(index2==size){return nums;}
                swap(nums,index1, index2);
                index2 = ++index1;
            }
        }
        return nums;
    }
    void swap(vector<int>& nums, int a, int b){
        if(nums[a] == nums[b]){
            return;
        }
        nums[a] = nums[a] ^ nums[b];
        nums[b] = nums[a] ^ nums[b];
        nums[a] = nums[a] ^ nums[b];
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
    //vector<int>nums = {4,2,4,4,1};
    vector<int>nums = {1,3,5,7,9};
    vector<int> res = te.exchange(nums);
    te.debug(res);
    return 0;
}

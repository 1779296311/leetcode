/*********************************************
*     ------------------------
*     ------------------------
*     file name: 80.cpp
*     author   : @ JY
*     date     : 2019--10--16
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        int removeDuplicates(vector<int>& nums){
            if(!nums.size()){
                return 0;
            }
            int current = 1;
            for(int i=2; i<nums.size(); i++){
                if(nums[i] != nums[current-1]){
                    nums[++current] = nums[i];
                }
            }
            return current+1;
        }
        int removeDuplicates(vector<int>& nums){
            if(!nums.size()){
                return 0;
            }
            if(nums.size() == 1){
                return 1;
            }
            if(nums.size() == 2){
                return 2;
            }
            int n;
            for(int i=0; i<nums.size()-2; i++){
                if(nums[i] == nums[i+1] && nums[i]==nums[i+2]){
                    for(int j=i+2; j<nums.size()-1;j++){
                        nums[j] = nums[j+1];
                    }
                    i--;
                }
            }
        }
};

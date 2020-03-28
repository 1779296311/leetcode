/********************************************* 
*     ------------------------
*     ------------------------
*     file name: 300.cpp
*     author   : @JY    
*     data     : 2019--09--11
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int lengthOfLIS(vector<int>& nums){
            int len = nums.size();
            int LIS = 1;
            vector<int> memo(len, 1);

            for(int i=1; i<len; i++){
                for(int j=0; j<len; j++){
                    if(nums[i]>nums[j] && memo[i] < memo[j]+1){
                        memo[i] = memo[j] + 1;
                    }
                }
                if(memo[i] > LIS){
                    LIS = memo[i];
                }
            }

            return LIS;
        }
        int lengLIS(vector<int>& nums){
            if(nums.size()== 0){
                return 0;
            }
            vector<int> memo;
            memo.push_back(nums[0]);

            for(int i=1; i<nums.size(); i++){
                if(nums[i]>memo.back()){
                    memo.push_back(numu[i]);
                }else{
                    memo[binary_search(memo,nums[i])] = num[i];
                }
            }
            return memo.size();
        }
        int binary_search(vectro<int>& memo, int target){

            int left  = 0;
            int right = memo.size() - 1;
            int index = -1;

            while(index == -1){
                int mid = (left+right)/2;
                if(target == memo[mid]){
                    index = mid;
                }else if(target < memo[mid]){
                    if(mid == 0 || target>memo[mid-1]){
                        index = mid;
                    }
                    right = mid - 1;
                }else if(target > memo[mid]){
                    if(mid == memo.size()-1 || target<memo[mid + 1]){
                        index = mid + 1;
                    }
                    left  = mid + 1;
                }
            }
            return index;
        }
};

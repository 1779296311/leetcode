/*********************************************
*     ------------------------
*     file name: 376.cpp
*     author   : @ JY
*     data     : 2019--09--12
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;

class Solution{
    public:
        int wiggleMaxLength_1(vector<int>& nums){
            int size = nums.size();
            if(size == 0){
                return 0;
            }
            if(size == 1 || (size == 2 && nums[0] != nums[1])){
                return size;
            }
            if(size == 2 && nums[0] == nums[1]){
                return 1;
            }

            vector<int> tmp(size);
            for(int i=1; i<size; i++){
                if(nums[i] - nums[i - 1] != 0){
                    tmp.push_back(nums[i] - nums[i-1]);
                }
            }
            if(tmp.size() == 0){
                return 1;
            }
            vector<int> memo(tmp.size(), 2);
            for(int i=1; i<tmp.size(); i++){
                if(tmp[i]*tmp[i-1] < 0){
                    memo[i] = memo[i-1] + 1;
                }else{
                    memo[i] = memo[i-1];
                }
            }
            return memo.back();
        }
        int wiggleMaxLength(vector<int>& nums){
            int size = nums.size();
            if(size==1 || size==2){
                return 1;
            }
            int flag  = 0;
            int __res = 1;
            for(int i=0; i<nums.size()-1; ++i){
                switch(flag){
                    case 0:
                        if(nums[i]>nums[i+1]){
                            flag = 1;
                            ++__res;
                        }else if(nums[i]<nums[i+1]){
                            flag = 2;
                            ++__res;
                        }
                        break;
                    case 1:
                        if(nums[i]<nums[i+1]){
                            ++__res;
                            flag = 2;
                        }
                        break;
                    case 2:
                        if(nums[i]>nums[i+1]){
                            ++__res;
                            flag = 1;
                        }
                        break;
                }
            }
            return __res;
        }

};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {1,17,5,10,5,16,8};
    cout<<te.wiggleMaxLength_1(nums)<<endl;
    cout<<te.wiggleMaxLength(nums)<<endl;
    return 0;
}

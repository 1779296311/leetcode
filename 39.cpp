/*********************************************
*     ------------------------
*     ------------------------
*     file name: 39.cpp
*     author   : @ JY
*     date     : 2019--10--04
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>
#include <ext/pool_allocator.h>
using  namespace  std;
/*
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates中的数字可以无限制重复被选取*/
class Solution{
    public:
        vector<vector<int>> combinationSum(vector<int>& candidates, int target){
            unordered_map<int, set<vector<int>>> nums;
            ::sort(candidates.begin(),candidates.end());
            vector<vector<int>> res;
            for(int i=0; i<=target; i++){
                for(auto num : candidates){
                    if(num == i){
                        nums[i].insert((vector<int>){num});
                        continue;
                    }else if(num < i){
                        for(vector<int> ivce : nums[i-num]){
                            ivce.push_back(num);
                            ::sort(ivce.begin(),ivce.end());  // 
                            if(nums[i].count(ivce) == 0){    //
                                nums[i].insert(ivce);
                            }
                        }
                    }
                    if(num > target){
                        break;
                    }
                }
            }
            for(auto it : nums[target]){
                res.push_back(it);
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums = {5,1,12,13,14};
    ::sort(nums.begin(),nums.end());
    for(auto s : nums){
        cout<<s;
    }
    cout<<endl;
    //vector<int> nums = {2,3,6,7};
    vector<vector<int>> res;
    res = te.combinationSum(nums,20);
    for(auto n : res){
        for(int m : n){
            cout<<m<<"--";
        }
        cout<<endl;
    }
    return 0;
}

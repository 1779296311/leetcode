/*********************************************
*     ------------------------
*     ------------------------
*     file name: 46.cpp
*     author   : @ JY
*     date     : 2020--05--07
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using  namespace  std;
//46. 全排列
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return partition1(nums);
    }
    vector<vector<int>> partition1(vector<int>&nums){
        if(nums.size() <= 1){
            return vector<vector<int>>{vector<int>{nums[0]}};
        }
        vector<vector<int>> res;
        for(int i=0; i<nums.size(); ++i){
            vector<int> tmp = nums;
            tmp.erase(tmp.begin()+i);
            int num = nums[i];
            vector<vector<int>>t = partition1(tmp);
            for(int j=0; j<t.size(); ++j){
                t[j].insert(t[j].begin(),num);
                res.push_back(t[j]);
            }
        }
        return res;
    }
    void debug(vector<int>& nums){
        vector<vector<int>> permutation = partition1(nums);
        for(int i=0; i<permutation.size(); ++i){
            for(int j=0; j<permutation[0].size(); ++j){
                cout<<permutation[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    vector<int> nums = {1,2,3,4};
    te.debug(nums);
    return 0;
}

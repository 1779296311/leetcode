/*********************************************
*     ------------------------
*     ------------------------
*     file name: 56.cpp
*     author   : @ JY
*     date     : 2020--04--30
**********************************************/
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution{
    struct cmp{
        bool operator()(vector<int>& a, vector<int>& b){
            return a[0] < b[0];
        }
    };
    public:
        vector<vector<int>> merge(vector<vector<int>>& nums){
            vector<vector<int>> res;
            sort(nums.begin(), nums.end(),cmp());
            int maxV;
            int minV;
            int j = 0;
            while(j<nums.size()){
                if(j<nums.size()){
                    maxV = nums[j][1];
                    minV = nums[j][0];
                }else{
                    break;
                }
                while(j<nums.size() && maxV >= nums[j][0]){
                    minV = min(minV,nums[j][0]);
                    maxV = max(maxV,nums[j][1]);
                    ++j;
                }
                vector<int>t;
                t.push_back(minV);
                t.push_back(maxV);
                res.push_back(t);
            }
            return res;
        }
        void debug(vector<vector<int>>& nums){
            for(int i=0; i<nums.size(); ++i){
                for(int j=0; j<nums[0].size(); ++j){
                    cout<<nums[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    //vector<vector<int>> nums = {{1,4},{4,5}};
    vector<vector<int>> nums = {{1,3},{2,6},{8,10},{15,18},{1,2},{3,5}};
    vector<vector<int>> res  = te.merge(nums);
    te.debug(res);
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 18.cpp
*     author   : @ JY
*     date     : 2019--10--11
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using  namespace  std;
class Solution{
    public:
        vector<vector<int>> fournum(vector<int>& nums, int target){
            vector<vector<int>> res;
            if(!nums.size() || nums.size() <= 3){
                return res;
            }
            int size = nums.size();
            sort(nums.begin(),nums.end());
            for(int i=0; i<size-3; i++){
                int first = i;
                for(int j=i+1; j<size-2; j++){
                    int second = j;
                    int third  = second+1;
                    int fourth = size-1;
                    while(third < fourth){
                        if(nums[first]+nums[second]+nums[third]+nums[fourth] < target){
                            third++;
                        }else if(nums[first]+nums[second]+nums[third]+nums[fourth] > target){
                            fourth--;
                        }else{
                            vector<int> tmp = {nums[first],nums[second],nums[third],nums[fourth]};
                            if(!count(res.begin(),res.end(),tmp)){
                                res.push_back(tmp);
                            }
                            third++;
                            fourth--;
                        }
                    }
                }
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    vector<vector<int>> res;
    vector<int> nums = {1,0,-1,0,-2,-2};
    Solution te;
    res = te.fournum(nums,0);
    for(vector<int> v : res){
        for(int a : v){
            cout<<a<<"__";
        }
        cout<<endl;
    }
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 78.cpp
*     author   : @ JY
*     date     : 2019--10--07
**********************************************/
#include <iostream>
#include <stdlib.h>
#include <vector>
using  namespace  std;
class Solution{
    public:
        vector<vector<int>> subsets(vector<int>& nums){
            int size = nums.size();
            int all  = 1<<size;
            vector<vector<int>> res;
            for(int i=0; i<all; i++){
                vector<int>tmp;
                for(int j=0; j<size; j++){
                    if(i & 1<<j){
                        tmp.push_back(nums[j]);
                    }
                }
                res.push_back(tmp);
            }
            return res;
        }
};

/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ3.cpp
*     author   : @ JY
*     date     : 2020--05--07
**********************************************/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_set<int> mp ;
        for(int i=0; i<nums.size(); ++i){
            if(mp.find(nums[i]) != mp.end()){
                return nums[i];
            }else{
                mp.insert(nums[i]);
            }
        }
        return -1;
    }
};

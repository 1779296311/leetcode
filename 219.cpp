/*********************************************
*     ------------------------
*     ------------------------
*     file name: 219.cpp
*     author   : @ JY
*     date     : 2020--05--06
**********************************************/
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int,int> mp;
        for(int i=0; i<nums.size(); ++i){
            if(mp.find(nums[i]) == mp.end()){
                mp[nums[i]] = i;
            }else if(i - mp[nums[i]] <= k){
                return true;
            }else{
                mp[nums[i]] = i;
            }
        }
        return false;
    }
};

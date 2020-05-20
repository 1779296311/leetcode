/*********************************************
*     ------------------------
*     ------------------------
*     file name: 217.cpp
*     author   : @ JY
*     date     : 2020--05--06
**********************************************/
#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
using  namespace  std;
class Solution{
    public:
        bool containsDuplicate(vector<int>& nums) {
            return set<int>(nums.begin(),nums.end()).size() != nums.size();
        }
};

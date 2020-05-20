/*********************************************
*     ------------------------
*     ------------------------
*     file name: JZ45.cpp
*     author   : @ JY
*     date     : 2020--05--13
**********************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
using  namespace  std;
class Solution {
public:
    struct cmp{
        bool operator()(string& a, string& b){
            return a+b < b+a;
        }
    };
    string minNumber(vector<int>& nums) {
        vector<string> tmp;
        for(int i=0; i<nums.size(); ++i){
            tmp.push_back(to_string(nums[i]));
        }
        sort(tmp.begin(),tmp.end(),cmp());
        string res = "";
        for(int i=0; i<tmp.size(); ++i){
            res = res + tmp[i];
        }
        return res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    vector<int> nums = {3,30,34,5,9};
    cout<<te.minNumber(nums)<<endl;
    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: 128.cpp
*     author   : @ JY
*     date     : 2020--05--01
**********************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <unordered_set>
#include <stdlib.h>
using  namespace  std;
//#define long long int
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int size = nums.size();
        unordered_set<int> hs;
        for(int i=0; i<size; ++i){
            hs.insert(nums[i]);
        }
        int res  = 0;
        int tmpn = 0;
        int tmpl = 0;
        for(int num : hs){
            if(num != INT_MAX && hs.find(num+1) != hs.end()){
                continue;
            }else{
                tmpn = num;
                tmpl = 1;
                while(num != INT_MIN && hs.find(tmpn-1) != hs.end()){
                    ++tmpl;
                    --tmpn;
                }
                res = max(res,tmpl);
            }
        }
        return (int)res;
    }
};
int main(int argc,const char *argv[]){
    Solution te;;
    //vector<int> nums = {100,4,200,3,1,2111,5,6,7,0};
    vector<int> nums = {INT_MIN ,INT_MIN+1};
    cout<<te.longestConsecutive(nums)<<endl;
    return 0;
}

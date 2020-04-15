/*********************************************
*     ------------------------
*     ------------------------
*     file name: longest_addNumIs_setValue.cpp
*     author   : @ JY
*     date     : 2020--03--29
**********************************************/
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
//最长 和=K的子数组
using  namespace  std;
class Solution{
    public:
        int get_sum_longest(vector<int>& nums,int value){
            int size = nums.size();
            map<int,int> mp;
            mp[0]     = -1;
            int sum   = 0;
            int __res = 0;
            for(int i=0; i<size; ++i){
                sum = sum + nums[i];
                if(mp.find(sum-value) != mp.end()){
                    __res = max(__res,i-mp[sum-value]);
                }
                if(mp.find(sum) == mp.end()){
                    mp[sum] = i;
                }
            }
            return __res;
        }
        int get_Even_Add_longest(vector<int>& nums){
            int size  = nums.size();
            int sum   = 0;
            int __res = 0;
            map<int,int> mp;
            mp[0]     = -1;
            for(int i=0; i<size; ++i){
                sum   = sum + (nums[i]&1?1:-1);
                if(mp.find(sum) != mp.end()){
                    __res = max(__res,i-mp[sum]);
                }else{
                    mp[sum] = i;
                }
            }
            return __res;
        }
        int get_xor_is_zero_longest(vector<int>& nums){
            int size  = nums.size();
            vector<int> dp(size,0);
            map<int,int> mp;
            mp[0]     = -1;
            int __xor = 0;
            int __res = 0;
            for(int i=0; i<size; ++i){
                __xor = __xor ^ nums[i];
                if(i>0){
                    dp[i] = dp[i-1];
                }
                if(mp.find(__xor) != mp.end()){
                    dp[i] = max(dp[i],(mp[__xor]==-1?0:dp[mp[__xor]])+1);
                }
                mp[__xor] = i;
                __res     = max(__res,dp[i]);
            }
            return __res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;
    vector<int> nums2 = {7,2,1,1,3,8,-2,6};
    vector<int> nums1 = {3,2,1,0,1,2,3,0};
    //cout<<te.get_sum_longest(nums2,7)<<endl;
    //cout<<te.get_Even_Add_longest(nums2)<<endl;
    cout<<te.get_xor_is_zero_longest(nums1)<<endl;
    return 0;
}

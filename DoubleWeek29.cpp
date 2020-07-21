/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek29.cpp
*     author   : @ JY
*     date     : 2020--06--28
**********************************************/
#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <unordered_set>
#include <stdlib.h>
#include <climits>
class Solution{
    public:
//给你一个整数数组 salary ，数组里每个数都是 唯一 的，其中 salary[i] 是第 i 个员工的工资。
//请你返回去掉最低工资和最高工资以后，剩下员工工资的平均值。
        double average(::std::vector<int>& salary){
            double sum = 0;
            int size   = salary.size();
            int Min    = INT_MAX;
            int Max    = INT_MIN;
            for(int i=0; i<size; ++i){
                Min = ::std::min(Min, salary[i]);
                Max = ::std::max(Min, salary[i]);
                sum += salary[i];
            }
            sum -= Min;
            sum -= Max;
            return sum/(size-2)*1.0;
        }
        double average_better(std::vector<int>& salary){
            if(salary.size()<=2)return 0;
            int max_v = *max_element(salary.begin(), salary.end());
            int min_v = *min_element(salary.begin(), salary.end());
            int sum   = std::accumulate(salary.begin(), salary.end(), 0);
            return (sum-max_v-min_v)/salary.size();
        }

//给你两个正整数 n 和 k 。
//如果正整数 i 满足 n % i == 0 ，那么我们就说正整数 i 是整数 n 的因子。
//考虑整数 n 的所有因子，将它们 升序排列 。请你返回第 k 个因子。如果 n 的因子数少于 k ，请你返回 -1 。
        int kthFactor(int n, int k){
            for(int i=1; i<=n; ++i){
                if(n%i == 0)--k;
                if(k==0)return i;
            }
            return -1;
        }

//给你一个二进制数组 nums ，你需要从中删掉一个元素。
//请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。
//如果不存在这样的子数组，请返回 0 
        int longestSubarray(::std::vector<int>& nums){
            ::std::unordered_map<int,int> hp;
            int r = 0;
            int size = nums.size();
            while(r<size){
                if(nums[r] == 1){
                    int l = r;
                    while(r<size && nums[r]==1)++r;
                    hp[l] = r-1;
                }
            }
            int res = 0;
            if(hp.size() == 0)return 0;
            if(hp.size() == 1){
                for(auto &n : hp){
                    if(n.first==0 && n.second==size)return size-1;
                    return n.second - n.first + 1;
                }
            }
            for(auto &n : hp){
                res = ::std::max(res, n.second-n.first+1);
                if(hp.count(n.second+2)){
                    res = ::std::max(res, hp[n.second+2]-n.first+1);
                }
            }
            return res;
        }
        int longestSubarray_better(::std::vector<int>& nums){
            int size = nums.size();
            int a    = 0;
            int b    = 0;
            int res  = 0;
            for(int i=0; i<size; ++i){
                if(nums[i]){
                    ++a;
                    ++b;
                    res = ::std::max(res, a);
                }else{
                    a = b;
                    b = 0;
                }
            }
            return res==size?--res:res;
        }
        int longestSubarray_comm(::std::vector<int>& nums, int k=1){
            int l     = 0;
            int r     = 0;
            int res   = 0;
            int size  = nums.size();
            int count = 0;
            while(r<size){
                if(!nums[r])++count;
                while(count>k){
                    if(!nums[l++])--count;
                }
                res = ::std::max(res, r++-l+1-k);
            }
            return res;
        }

//给你一个整数 n 表示某所大学里课程的数目，编号为 1 到 n ，数组 dependencies 中， dependencies[i] = [xi, yi]  表示一个先修课的关系，也就是课程 xi 必须在课程 yi 之前上。同时你还有一个整数 k 。
//在一个学期中，你 最多 可以同时上 k 门课，前提是这些课的先修课在之前的学期里已经上过了。
//请你返回上完所有课最少需要多少个学期。题目保证一定存在一种上完所有课的方式。
        int minNumberOfSemesters(int n, ::std::vector<::std::vector<int>>& d, int k){
            ::std::vector<int> pre((1<<n), 0);
            for(auto &n : d){
                pre[(1<<(n[1]-1))] |= (1<<(n[0]-1));
            }
            for(int i=0; i<(1<<n); ++i){
                pre[i] = pre[i^(i&-i)] | pre[i&-i];
            }
            ::std::vector<int> dp((1<<n), 365);
            dp[0] = 0;
            for(int i=1; i<(1<<n); ++i){
                for(int j=i; j; j=(j-1)&i){
                    if(__builtin_popcount(j) > k)continue;
                    if((pre[j]&(i^j)) != pre[j])continue;
                    dp[i] = ::std::min(dp[i], dp[i^j]+1);
                }
            }
#ifdef debug
   for(int i=0; i<(1<<n); ++i){
       ::std::cout<<::std::bitset<8>(pre[i])<<::std::endl;
   }
#endif
            return dp[(1<<n)-1];
        }
        ///------------------------wrong------------------------------------
        int fuck_minNumberOfSemesters(int n, ::std::vector<::std::vector<int>>&d, int k){
            int size = d.size();
            if(!size){
                int res = size/k;
                return res*k==size?res:++res;
            }
            ::std::vector<::std::unordered_set<int>>hp(n+1);
            for(int i=1; i<=n; ++i){
                int j = 0;
                for(; j<size; ++j){
                    if(d[j][1] == i)break;
                }
                if(j==size)hp[0].insert(i);
            }
            for(int i=1; i<=n; ++i){
                for(auto n=hp[i-1].begin(); n!=hp[i-1].end(); ++n){
                    for(auto &x : d){
                        if(x[0] == *n){
                            if(hp[i].count(x[1]))continue;
                            hp[i].insert(x[1]);
                        }
                    }
                }
                if(hp[i].size() == 0)break;
            }
            //for(int i=0; i<hp.size(); ++i){
                //for(auto n=hp[i].begin(); n!=hp[i].end(); ++n){
                    //::std::cout<<*n<<"--";
                //}
                //::std::cout<<::std::endl;
            //}
            int res = 0;
            for(auto &n : hp){
                if(!n.size())return res;
                int t = n.size()/k;
                res += t*k==n.size()?t:++t;
            }
            return res;
        }
};
int main(int argc,const char *argv[]){
    Solution te;

    //::std::vector<::std::vector<int>> nums = {{2,1},{3,1},{4,1},{1,5}};
    ::std::vector<::std::vector<int>> nums = {{2,1},{3,1},{1,4}};
    int n = 4;
    int k = 3;
    ::std::cout<<te.minNumberOfSemesters(n,nums,k)<<::std::endl;

    //::std::vector<int> nums = {1,1,1,1,1,1,1,1,1,1};
    //int k = 2;
    //::std::cout<<te.longestSubarray_better(nums)<<::std::endl;
    //::std::cout<<te.longestSubarray_comm(nums, k)<<::std::endl;
    return 0;
}

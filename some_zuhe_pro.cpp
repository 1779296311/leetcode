/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_zuhe_pro.cpp
*     author   : @ JY
*     date     : 2020--07--28
**********************************************/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdlib.h>

class Solution{
    public:
//给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
        std::vector<std::vector<int>> conbinationSum_0(int n, int k){
            std::vector<std::vector<int>> res;
            std::vector<int> tmp;
            dfs(res, k, 1, n, tmp);
            return res;
        }
        void dfs(std::vector<std::vector<int>>& res, int k,
                 int begin, int n, std::vector<int>& tmp){
            if(tmp.size() == k){
                res.push_back(tmp);
                return;
            }
            for(int i=begin; i<=n; ++i){
                tmp.push_back(i);
                dfs(res, k, i+1, n, tmp);
                tmp.pop_back();
            }
        }
//----------------------------------------------------------------------
//给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。 candidates 中的数字可以无限制重复被选取。
        std::vector<std::vector<int>> conbinationSum_1(std::vector<int>& c, int target){
            std::vector<int> tmp;
            std::vector<std::vector<int>> res;
            dfs(res, target, 0, c, tmp);
            return res;
        }
        void dfs(std::vector<std::vector<int>>& res, int target, int begin,
                 std::vector<int>&c, std::vector<int>& tmp){
            if(target<0)return;
            if(0 == target){
                res.push_back(tmp);
                return;
            }
            int size = c.size();
            for(int i=begin; i<size; ++i){
                tmp.push_back(c[i]);
                dfs(res, target-c[i], i, c, tmp);
                tmp.pop_back();
            }
        }
//----------------------------------------------------------------------
//给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。 candidates 中的每个数字在每个组合中只能使用一次。
        std::vector<std::vector<int>> conbinationSum_2(std::vector<int>& c, int target){
            std::vector<std::vector<int>> res;
            std::vector<int> tmp;
            dfs(res, tmp, c, target, 0);
            return res;
        }
        void dfs(std::vector<std::vector<int>>& res, std::vector<int>& tmp,
                 std::vector<int>& c, int target, int begin){
            if(target<0)return;
            if(!target){
                res.push_back(tmp);
                return;
            }
            int size = c.size();
            for(int i=begin; i<size; ++i){
                tmp.push_back(c[i]);
                dfs(res, tmp, c, target-c[i], i+1);
                tmp.pop_back();
            }
        }
        std::vector<std::vector<int>> conbinationSum_2_pack(std::vector<int>& c, int target){
            std::vector<std::vector<std::vector<int>>> dp(target+1);
            int size = c.size();
            dp[0] = {{}};
            for(int i=0; i<size; ++i){
                for(int t=target; t>=c[i]; --t){
                    auto tmp = dp[t-c[i]];
                    for(auto &r : tmp){
                        r.push_back(c[i]);
                        dp[t].push_back(r);
                    }
                }
            }
            std::vector<std::vector<int>> res = dp[target];
            for(auto &n : res)std::sort(n.begin(), n.end());
            std::sort(res.begin(), res.end());
            res.erase(std::unique(res.begin(), res.end()), res.end());
            return res;
        }
//----------------------------------------------------------------------
//找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。
        std::vector<std::vector<int>> conbinationSum_3(int k, int t){
            std::vector<std::vector<int>> res;
            std::vector<int> tmp;
            dfs(res, tmp, t, k, 1);
            return res;
        }
        void dfs(std::vector<std::vector<int>>& res,
                std::vector<int>& tmp, int t, int k, int beign){
            if(t<0 || t<tmp.size())return;
            if(!t && tmp.size()==k){
                res.push_back(tmp);
                return;
            }
            for(int i=beign; i<=9; ++i){
                tmp.push_back(i);
                dfs(res, tmp, t-i, k, i+1);
                tmp.pop_back();
            }
        }
//----------------------------------------------------------------------
//给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
    int combinationSum_4(std::vector<int>& nums, int target) {
        std::vector<unsigned long long> dp(target+1, 0);
        dp[0] = 1;
        for(int i=1; i<=target; ++i){
            for(int j=0; j<nums.size(); ++j){
                if(nums[j]<=i)dp[i] += dp[i-nums[j]];
            }
        }
        return dp[target];
    }
//我们有一组排序的数字 D，它是  {'1','2','3','4','5','6','7','8','9'} 的非空子集。（请注意，'0' 不包括在内。） 现在，我们用这些数字进行组合写数字，想用多少次就用多少次。例如 D = {'1','3','5'}，我们可以写出像 '13', '551', '1351315' 这样的数字。 返回可以用 D 中的数字写出的小于或等于 N 的正整数的数目。
    int atMostNGivenDigitSet(std::vector<std::string>& D, int N){
    }
    int atMostNGivenDigitSet_fuck(std::vector<std::string>& D, int N){
        int res = 0;
        std::vector<int> dp(N+5, -1);
        return dfs(0, dp, D, N);
    }
    int dfs(unsigned long long num, std::vector<int>& dp, std::vector<std::string>& D, int N){
        if(num>N)return 0;
        if(dp[num] != -1)dp[num];
        int res = 1;
        int size = D.size();
        for(int i=0; i<size; ++i){
            res += dfs(num*10+(D[i][0]-'0'), dp, D, N);
        }
        return res;
    }
};


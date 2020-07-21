/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK197.cpp
*     author   : @ JY
*     date     : 2020--07--13
**********************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stdlib.h>
class Solution{
    public:
//给你一个整数数组 nums 。 如果一组数字 (i,j) 满足 nums[i] == nums[j] 且 i < j ，就可以认为这是一组 好数对 。 返回好数对的数目。
        int numAdenticalPairs(::std::vector<int>& nums){
            int res = 0;
            for(int i=0; i<nums.size(); ++i){
                for(int j=i+1; j<nums.size(); ++j){
                    res += nums[i]==nums[j];
                }
            }
            return res;
        }
//给你一个二进制字符串 s（仅由 '0' 和 '1' 组成的字符串）。
//返回所有字符都为 1 的子字符串的数目。
//由于答案可能很大，请你将它对 10^9 + 7 取模后返回。
        int numSub(::std::string s){
            long long left  = 0;
            long long right = -1;
            long long size  = s.length();
            long long res   = 0;
            long long MOD   = 1e9+7;
            while(right<size){
                while(right<size && s[++right]=='0');
                left = right;
                while(right<size && s[++right]=='1');
                res  = (res + (((right-left)*(right-left+1))>>1)) % MOD;
            }
            return res % MOD;
        }
//你一个由 n 个节点（下标从 0 开始）组成的无向加权图，该图由一个描述边的列表组成，其中 edges[i] = [a, b] 表示连接节点 a 和 b 的一条无向边，且该边遍历成功的概率为 succProb[i] 。
//指定两个节点分别作为起点 start 和终点 end ，请你找出从起点到终点成功概率最大的路径，并返回其成功概率。
//如果不存在从 start 到 end 的路径，请 返回 0 。只要答案与标准答案的误差不超过 1e-5 ，就会被视作正确答案
        double maxProbability(int n, ::std::vector<::std::vector<int>>& edges, ::std::vector<double>& succProb, int start, int end){
            int size = edges.size();
            ::std::vector<::std::vector<::std::pair<double, int>>> p(n, ::std::vector<::std::pair<double, int>>());
            for(int i=0; i<size; ++i){
                p[edges[i][0]].push_back({succProb[i], edges[i][1]});
                p[edges[i][1]].push_back({succProb[i], edges[i][0]});
            }
            ::std::vector<int> visited(n , 0);
            ::std::priority_queue<::std::pair<double, int>> q;
            q.push({1.0, start});
            while(q.size()){
                auto [w,cur] = q.top();
                q.pop();
                if(visited[cur])continue;
                ++visited[cur];
                if(cur==end)return w;
                for(auto [w1, next] : p[cur]){
                    if(visited[next])continue;
                    q.push({w1*w, next});
                }
            }
            return 0;
        }
};

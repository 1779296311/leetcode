/*********************************************
*     ------------------------
*     ------------------------
*     file name: DoubleWeek30.cpp
*     author   : @ JY
*     date     : 2020--07--12
**********************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdlib.h>
class Solution{
    public:
//给你一个字符串 date ，它的格式为 Day Month Year ，其中：
//Day 是集合 {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"} 中的一个元素。
//Month 是集合 {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"} 中的一个元素。
//Year 的范围在 ​[1900, 2100] 之间。
        ::std::string reformatDate(::std::string& date){
            ::std::unordered_map<::std::string, ::std::string> mp = {
                {"Jan","01"},{"Feb","02"},{"Mar","03"},{"Apr","04"},{"May","05"},{"Jun","06"},{"Jul","07"},{"Aug","08"},{"Sep","09"},{"Oct","10"},{"Nov","11"},{"Dec","12"}
            };
            ::std::string tmp;
            ::std::string s1;
            ::std::string s2;
            ::std::string s3;

            ::std::stringstream ss(date);

            ss >> tmp;
            s1 = ::std::to_string(::std::stoi(tmp));

            ss >> tmp;
            s2 = mp[tmp];

            ss >> tmp;
            s3 = ::std::to_string(::std::stoi(tmp));

            return s3 + "-" + s2 + "-" + s1;
        }
//给你一个数组 nums ，它包含 n 个正整数。你需要计算所有非空连续子数组的和，并将它们按升序排序，得到一个新的包含 n * (n + 1) / 2 个数字的数组。
//请你返回在新数组中下标为 left 到 right （下标从 1 开始）的所有数字和（包括左右端点）。由于答案可能很大，请你将它对 10^9 + 7 取模后返回。
        int rangeSum(::std::vector<int>& nums, int n, int left, int right){
            ::std::vector<::std::vector<int>> sum(n+1, ::std::vector<int>(n+1, 0));
            ::std::priority_queue<int, ::std::vector<int>, ::std::greater<int>> q;
            for(int i=1; i<=n; ++i){
                for(int j=i; j<=n; ++j){
                    sum[i][j] += sum[i][j-1] + nums[j];
                    q.push(sum[i][j]);
                }
            }
            while(left--){
                q.pop();
            }
            int res = 0;
            int num = right - left + 1;
            while(right--){
                res += q.top();
                res %= 1000000007;
                q.pop();
            }
            return res % 1000000007;
        }
//给你一个数组 nums ，每次操作你可以选择 nums 中的任意一个数字并将它改成任意值。
//请你返回三次操作后， nums 中最大值与最小值的差的最小值。
        int minDifference(::std::vector<int>& nums){
            int size = nums.size();
            if(size<=4)return 0;
            ::std::sort(nums.begin(), nums.end());

            int res = ::std::min(nums[size-1]-nums[3], nums[size-2] - nums[2]); //1 2  size-1
            res     = ::std::min(res, nums[size-3] - nums[1]);  // 1 size-1 size-2
            res     = ::std::min(res, nums[size-4] - nums[0]);  // size-3 size-2 size1-
            return res;
        }
//Alice 和 Bob 两个人轮流玩一个游戏，Alice 先手。
//一开始，有 n 个石子堆在一起。每个人轮流操作，正在操作的玩家可以从石子堆里拿走 任意 非零 平方数 个石子。
//如果石子堆里没有石子了，则无法操作的玩家输掉游戏。
//给你正整数 n ，且已知两个人都采取最优策略。如果 Alice 会赢得比赛，那么返回 True ，否则返回 False 。
        bool storeGameIV(int n){
            ::std::vector<bool> dp(n, false);
            for(int i=n; i>=0; --i){
                for(int j=1; n<=i+j*j; ++j){
                    if((dp[i]= !dp[i+j*j]))break;
                }
            }
            return dp[0];
        }
};

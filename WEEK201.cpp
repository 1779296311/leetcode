/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK201.cpp
*     author   : @ JY
*     date     : 2020--08--10
**********************************************/
#include <iostream>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdlib.h>
class Solution{
    public:
//给你一个由大小写英文字母组成的字符串 s 。 一个整理好的字符串中，两个相邻字符 s[i] 和 s[i + 1] 不会同时满足下述条件： 0 <= i <= s.length - 2 s[i] 是小写字符，但 s[i + 1] 是相同的大写字符；反之亦然 。 请你将字符串整理好，每次你都可以从字符串中选出满足上述条件的 两个相邻 字符并删除，直到字符串整理好为止。 请返回整理好的 字符串 。题目保证在给出的约束条件下，测试样例对应的答案是唯一的。
//注意：空字符串也属于整理好的字符串，尽管其中没有任何字符。 
        std::string makeGood(std::string& s){
            int size = s.length();
            int pre  = 0;
            int end  = 1;
            while(end<size){
                if(abs(s[pre]-s[end]) == 32){
                    s.erase(pre, 1);
                    s.erase(end-1, 1);
                    if(pre)--end, --pre;
                    size -= 2;
                }else{
                    ++pre;
                    ++end;
                }
            }
            return s;
        }
//给你两个正整数 n 和 k，二进制字符串  Sn 的形成规则如下： S1 = "0" 当 i > 1 时，Si = Si-1 + "1" + reverse(invert(Si-1)) 其中 + 表示串联操作，reverse(x) 返回反转 x 后得到的字符串，而 invert(x) 则会翻转 x 中的每一位（0 变为 1，而 1 变为 0）
        char findKthBit(int n, int k){
            if(n==1)return '0';
            int mid = 1<<(n-1);
            if(mid == k)return '1';
            if(mid>k)return findKthBit(n-1, k);
            return 97 - findKthBit(n-1, (mid<<1)-k);
        }
        char findKthBit_fuck(int n,int k){
            std::string lnext = "0", rnext = "1";
            std::string l , r;
            for(int i=1; i<n; ++i){
                l  = lnext;
                l += "1";
                l += rnext;

                r  = lnext;
                r += "0";
                r += rnext;

                lnext = l;
                rnext = r;
            }
            return l[k-1];
        }
//给你一个数组 nums 和一个整数 target 。 请你返回 非空不重叠 子数组的最大数目，且每个子数组中数字和都为 target 。
        int maxNonOverlapping(std::vector<int>&nums, int target){
            std::unordered_map<int, int> mp;
            mp[0] = -1;
            int last = -1;
            int sum  = 0;
            int size = nums.size();
            int res  = 0;
            for(int i=0; i<size; ++i){
                sum += nums[i];
                if(mp.count(sum-target) && mp[sum-target] + 1> last){
                    ++res;
                    last = i;
                }
                mp[sum] = i;
            }
            return res;
        }
        int maxNonOverlapping_fuck(std::vector<int>& nums, int target){
            int size = nums.size();
            std::vector<int> dp(size, 0);
            std::vector<int> sums(nums);
            for(int i=1; i<size; ++i)sums[i] += sums[i-1];
            dp[0] = target==nums[0];
            for(int i=1; i<size; ++i){
                for(int j=i-1; j>=1; --j){
                    if(sums[i]==target)dp[i] = std::max(dp[i], 1);
                    dp[i] = std::max(dp[i], dp[i-1]);
                    if(sums[i]-sums[j]+nums[j]== target){
                        dp[i] = std::max(dp[i], dp[j-1]+1);
                    }
                }
            }
            return dp[size-1];
        }
//给你一个整数数组 cuts ，其中 cuts[i] 表示你需要将棍子切开的位置。 你可以按顺序完成切割，也可以根据需要更改切割的顺序。 每次切割的成本都是当前要切割的棍子的长度，切棍子的总成本是历次切割成本的总和。对棍子进行切割将会把一根木棍分成两根较小的木棍（这两根木棍的长度和就是切割前木棍的长度）。请参阅第一个示例以获得更直观的解释。
        int minCut(int n, std::vector<int>& cuts){
            cuts.push_back(0);
            cuts.push_back(n);
            int size = cuts.size();
            std::sort(cuts.begin(), cuts.end());
            std::vector<std::vector<int>> dp(size, std::vector<int>(size, INT_MAX>>1));
            for(int j=1; j<size; ++j){
                for(int i=j; i>=1; --i){
                    if(i==j){
                        dp[i][j] = 0;
                        continue;
                    }
                    for(int m=i; m<j; ++m){
                        dp[i][j] = std::min(dp[i][j], dp[i][m]+dp[m+1][j]+cuts[j]-cuts[i-1]);
                    }
                }
            }
            return dp[1][size-1];
        }
};

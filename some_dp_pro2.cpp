/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_dp_pro2.cpp
*     author   : @ JY
*     date     : 2020--08--05
**********************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stdlib.h>
class Trie{
    public:
        Trie(){ next = std::vector<Trie*>(26, nullptr);}
    public:
        void insert(std::string& word){
            auto root = this;
            for(auto &c : word){
                if(root->next[c-'a'] == nullptr)root->next[c-'a'] = new Trie();
                root = root->next[c-'a'];
            }
            root->str_end = true;
        }
        bool search(std::string& word, int index, int count){
            auto *root = this;
            int size = word.size();
            for(int i=index; i<size; ++i){
                if(root->next[word[index]-'a'] == nullptr)return false;
                if((root = root->next[word[i]-'a'])->str_end){
                    if(i==word.size()-1)return count>0;
                    if(search(word, i+1, count+1))return true;
                }
            }
            return false;
        }
    private:
        bool str_end = false;
        std::vector<Trie*> next;
};
class Solution{
    public:
//帮派里有 G 名成员，他们可能犯下各种各样的罪行。 第 i 种犯罪会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与。 让我们把这些犯罪的任何子集称为盈利计划，该计划至少产生 P 的利润。 有多少种方案可以选择？因为答案很大，所以返回它模 10^9 + 7 的值。
        int profitableSchemes(int G, int P, std::vector<int>&group, std::vector<int>&profit){
            int MOD = 1e9 + 7;
            std::vector<std::vector<long long>> dp(G+1, std::vector<long long>(P+1, 0));
            for(int i=0; i<=G; ++i)dp[i][0] = 1;
            int size = profit.size();
            for(int i=1; i<=size; ++i){
                int g = group[i-1];
                int p = profit[i-1];
                for(int j=G; j>=g; --j){
                    for(int k=P; k>=0; --k){
                        dp[j][k] = (dp[j][k] + dp[j-g][std::max(k-p, 0)]) % MOD;
                    }
                }
            }
            return dp[G][P];
        }
//定一个不含重复单词的列表，编写一个程序，返回给定单词列表中所有的连接词。 连接词的定义为：一个字符串完全是由至少两个给定数组中的单词组成的。
        std::vector<std::string> findAllConcatenatedWordsInADict(std::vector<std::string>& words){
            Trie* root = new Trie();
            for(auto &wd : words)root->insert(wd);
            std::vector<std::string> res;
            for(auto &wd : words){
                if(root->search(wd, 0, 0))res.push_back(wd);
            }
            return res;
        }
        std::vector<std::string> findAllConcatenatedWordsInADict_fuck(std::vector<std::string>& words){
            std::vector<std::string> res;
            int size = words.size();
            for(int i=0; i<size; ++i){
                if(dfs(words[i], 0, words, 0))res.push_back(words[i]);
            }
            return res;
        }
        bool dfs(std::string& word, int index, std::vector<std::string>&words, int mp){
            if(index==word.size())return mp>1;
            int size = words.size();
            for(int j=0; j<size; ++j){
                auto wd = words[j];
                if(wd[0]==word[index]){
                    int i = 0;
                    for(; i<wd.size() && index+i<word.size() && wd[i]==word[index+i]; ++i);
                    if(i!=wd.size())continue;
                    if(dfs(word, index+wd.size(), words, mp+1))return true;
                }
            }
            return false;
        }
//给定一个非负整数 n，计算各位数字都不同的数字 x 的个数，其中 0 ≤ x < 10n 。
        int countNumbersWithUniqueDigits(int n){
            if(!n)return 1;
            int res = 10,num = 9*9;
            for(int i = 2; i <= std::min(n,10); i++) res += num, num = num*(10-i);
            return res;
        }
//给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。设计一个算法使得这 m 个子数组各自和的最大值最小。
        int splitArray(std::vector<int>&nums, int n){
            int size = nums.size();
            std::vector<long long> sums(size, 0);
            for(int i=1; i<size; ++i)sums[i] = sums[i-1] + nums[i];
            std::vector<long long> dp_0(sums);
            for(int k=2; k<=n; ++k){
                for(int i=size-1; i>=k-1; --i){
                    for(int j=k-2; j<i; ++j){
                        dp_0[i] = std::min(dp_0[i], std::max(dp_0[j], sums[i]-sums[j]));
                    }
                }
            }
            return dp_0[size-1];
        }
//我们将给定的数组 A 分成 K 个相邻的非空子数组 ，我们的分数由每个子数组内的平均值的总和构成。计算我们所能得到的最大分数是多少。 注意我们必须使用 A 数组中的每一个数进行分组，并且分数不一定需要是整数。
        double largestSumOfAverages(std::vector<int>& A, int K){
            int size  = A.size();
            std::vector<double> dp(size, 0);
            std::vector<int> sum(A);

            for(int i=1; i<size; ++i)sum[i] += sum[i-1];
            for(int i=0; i<size; ++i)dp[i]   = sum[i]/(i+1);

            for(int k=2; k<=K; ++k){
                for(int i=size-1; i>=k-1; --i){
                    for(int j=k-2; j<i; ++j){
                        dp[i] = std::max(dp[i], dp[j]+(sum[i]-sum[j])/(i-j));
                    }
                }
            }
            return dp[size-1];
        }

 //三步问题。有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶或3阶。实现一种方法，计算小孩有多少种上楼梯的方式。结果可能很大，你需要对结果模1000000007。
        int waysToStep(int n){
            long long mod = 1e9 + 7;
            long long i_1 = 1;
            if(n==1)return i_1;
            long long i_2 = 2;
            if(n==2)return i_2;
            long long i_3 = 4;
            if(n==3)return i_3;
            for(long long i=4; i<=n; ++i){
                long long tmp = (i_1 + i_2 + i_3) % mod;
                i_1 = i_2;
                i_2 = i_3;
                i_3 = tmp;
            }
            return i_3 % mod;
        }
//我们有一个非负整数数组 A。 对于每个（连续的）子数组 B = [A[i], A[i+1], ..., A[j]] （ i <= j），我们对 B 中的每个元素进行按位或操作，获得结果 A[i] | A[i+1] | ... | A[j]。 返回可能结果的数量。 （多次出现的结果在最终答案中仅计算一次。）
        int subarrayBiwWiseORs(std::vector<int>& A){
            int size = A.size();
            std::unordered_set<int> mp;
            for(int i=0; i<size; ++i){
                mp.insert(A[i]);
                for(int j=i-1; j>=0; --j){
                    if((A[i] | A[j])==A[j])break;
                    mp.insert((A[j] |= A[i]));
                }
            }
            return mp.size();
        }
//给出两个字符串 str1 和 str2，返回同时以 str1 和 str2 作为子序列的最短字符串。如果答案不止一个，则可以返回满足条件的任意一个答案。
        std::string shortestCommonSupersquence(std::string s1, std::string s2){
            int len1 = s1.length();
            int len2 = s2.length();
            std::vector<std::vector<std::string>> dp(len1+1, std::vector<std::string>(len2+1,""));
            for(int i=1; i<=len1; ++i){
                for(int j=1; j<=len2; ++j){
                    if(s1[i-1] == s2[j-1]){
                        dp[i][j] = dp[i-1][j-1] + s1[i-1];
                    }else{
                        dp[i][j] = dp[i-1][j].size()>dp[i][j-1].size()?dp[i-1][j]:dp[i][j-1];
                    }
                }
            }
            std::string res = "";
            int i = 0;
            int j = 0;
            for(char c : dp[len1][len2]){
                while(i<len1 && s1[i++]!=c)res += s1[i-1];
                while(j<len2 && s2[j++]!=c)res += s2[j-1];
                res += c;
            }
            if(i<len1)res += s1.substr(i);
            if(j<len2)res += s2.substr(j);
            return res;
        }
//数组的每个索引作为一个阶梯，第 i个阶梯对应着一个非负数的体力花费值 cost[i](索引从0开始)。 每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。 您需要找到达到楼层顶部的最低花费。在开始时，你可以选择从索引为 0 或 1 的元素作为初始阶梯。
    int minCostClimbingStairs(std::vector<int>& cost) {
        int size = cost.size();
        if(size<=2)return std::min(cost[0], cost[1]);
        std::vector<int> dp(size+1, INT_MAX>>1);
        dp[1] = dp[0] = 0;
        dp[2] = std::min(cost[0], cost[1]);
        for(int i=3; i<size; ++i){
            dp[i] = std::min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]);
        }
        return dp[size-1];
    }
//给你一个 m * n 的矩阵 seats 表示教室中的座位分布。如果座位是坏的（不可用），就用 '#' 表示；否则，用 '.' 表示。 学生可以看到左侧、右侧、左上、右上这四个方向上紧邻他的学生的答卷，但是看不到直接坐在他前面或者后面的学生的答卷。请你计算并返回该考场可以容纳的一起参加考试且无法作弊的最大学生人数。 学生必须坐在状况良好的座位上。
        int maxStudents(std::vector<std::vector<char>>& seats) {
            int m = seats.size();
            int n = seats[0].size();
            std::vector<std::vector<int>> dp(m+1, std::vector<int>((1<<n), 0));
            std::vector<int> L(m+1, 0);
            std::vector<int> ok;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    L[i+1] = (L[i+1]<<1) | (seats[i][j]=='.');
                }
            }
            ok.push_back(0);
            for(int i=1; i<(1<<n); ++i){
                if(i&(i>>1))continue;
                if((L[1]&i)==i)dp[1][i] = __builtin_popcount(i);
                ok.push_back(i);
            }
            for(int i=2; i<=m; ++i){
                for(auto &now : ok){
                    if((now&L[i]) != now)continue;
                    for(auto &pre : ok){
                        if((pre&L[i-1]) != pre)continue;
                        if(now&(pre>>1) || now&(pre<<1))continue;
                        dp[i][now] = std::max(dp[i][now], dp[i-1][pre] + __builtin_popcount(now));
                    }
                }
            }
            int res = 0;
            for(int i=0; i<=m; ++i)res = std::max(res, *max_element(dp[i].begin(), dp[i].end()));
            return res;
        }
//给定一个字符串 S，找出 S 中不同的非空回文子序列个数，并返回该数字与 10^9 + 7 的模。
//通过从 S 中删除 0 个或多个字符来获得子序列。
//如果一个字符序列与它反转后的字符序列一致，那么它是回文字符序列。
        const int MOD = 1e9 + 7;
        int countPalindromicSubsquence(std::string& S){
            int size = S.length();
            std::vector<std::vector<int>> pre(size,std::vector<int>(4, -1)), next(size,std::vector<int>(4, -1));
            std::vector<std::vector<long long>> dp(size, std::vector<long long>(size, -1));
            std::vector<int> tmp(4, -1);
            for(int i=0; i<size; ++i){
                tmp[S[i]-'a'] = i;
                pre[i][0]     = tmp[0];
                pre[i][1]     = tmp[1];
                pre[i][2]     = tmp[2];
                pre[i][3]     = tmp[3];
            }
            fill(tmp.begin(), tmp.end(),-1);
            for(int i=size-1; i>=0; --i){
                tmp[S[i]-'a'] = i;
                next[i][0]    = tmp[0];
                next[i][1]    = tmp[1];
                next[i][2]    = tmp[2];
                next[i][3]    = tmp[3];
            }
            return -1+dfs(pre, next, dp, 0, size-1) % MOD;
        }
        long long dfs(std::vector<std::vector<int>>& pre,std::vector<std::vector<int>>& next, std::vector<std::vector<long long>>& dp, int i, int j){
            if(dp[i][j] !=-1)return dp[i][j];
            long  long res = 0;
            if(i<=j){
                for(int k=0; k<4; ++k){
                    int i1 = next[i][k];
                    int j1 = pre[j][k];
                    if(i1 < j1)++res;
                    if(i1>=0 && i1<j1)res = (res + dfs(pre, next, dp, i1+1, j1-1));
                }
            }
            return dp[i][j] = res;
        }
        int conutPalindromicSubsequence_fuck(std::string S){
            std::unordered_map<std::string, int> mp;
            int res = 0;
            dfs(res, S, 0, "", mp);
            return res;
        }
        void dfs(int& res, std::string& S,int index,std::string t,
                 std::unordered_map<std::string, int>& mp){
            if(index==S.length()){
                if(mp.count(t))return;
                res += (mp[t]=is_palindrome(t));
                return;
            }
            dfs(res, S, index+1, t+S[index], mp);
            dfs(res, S, index+1, t, mp);
        }
        bool is_palindrome(std::string& s){
            int i = -1; 
            int j = s.length();
            while(i<j && s[++i]==s[--j]);
            return i==j;
        }
//设想有个机器人坐在一个网格的左上角，网格 r 行 c 列。机器人只能向下或向右移动，但不能走到一些被禁止的网格（有障碍物）。设计一种算法，寻找机器人从左上角移动到右下角的路径。
        std::vector<std::vector<int>> pathWIthObsacles(std::vector<std::vector<int>>& grid){
            int size_i = grid.size();
            int size_j = grid[0].size();
            std::vector<std::vector<int>> dp(size_i+1, std::vector<int>(size_j+1, 0));

            for(int i=size_i-1; i>=0; --i)dp[i][size_j-1] = dp[i+1][size_j-1] + grid[i][size_j-1];
            for(int i=size_j-1; i>=0; --i)dp[size_i-1][i] = dp[size_i-1][i+1] + grid[size_i-1][i];

            for(int i=size_i-2; i>=0; --i){
                for(int j=size_j-2; j>=0; --j){
                    dp[i][j] = std::min(dp[i][j+1], dp[i+1][j]) + grid[i][j];
                }
            }
            if(dp[0][0])return {};
            std::vector<std::vector<int>> res;
            int sum = dp[0][0];
            int i = 0;
            int j = 0;
            while(size_i-1 > i || size_j-1 > j){
                sum -= grid[i][j];
                res.push_back({i, j});
                if(i!=size_i-1 && sum == dp[i+1][j]){
                    ++i;
                }else{
                    ++j;
                }
            }
            res.push_back({size_i-1, size_j-1});
            return res;
        }
//堆箱子。给你一堆n个箱子，箱子宽 wi、深 di、高 hi。箱子不能翻转，将箱子堆起来时，下面箱子的宽度、高度和深度必须大于上面的箱子。实现一种方法，搭出最高的一堆箱子。箱堆的高度为每个箱子高度的总和。 输入使用数组[wi, di, hi]表示每个箱子。
        int pileBox(std::vector<std::vector<int>>& box){
            int size = box.size();
            std::vector<int> dp(size+1, 0);
            sort(box.begin(), box.end(), [](auto &a, auto &b){
                    return a[0]<b[0];
            });
            for(int i=0; i<size; ++i){
                dp[i] = box[i][2];
                for(int j=i-1; j>=0; --j){
                    if(box[i][0]>box[j][0]&&
                       box[i][1]>box[j][1]&&
                       box[i][2]>box[j][2]){
                        dp[i] = std::max(dp[i], dp[j] + box[i][2]);
                    }
                }
            }
            return *max_element(dp.begin(), dp.end());
        }
//给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
        int findTargetSumWays(std::vector<int>& nums, int S){
            int size = nums.size();
            return dfs(nums, 0, S);
        }
        int dfs(std::vector<int>& nums, int index, int S){
            if(!S && index==nums.size())return 1;
            if(index>nums.size())return 0;
            int    res  = dfs(nums, index+1, S-nums[index]);
            return res += dfs(nums, index+1, S+nums[index]);
        }
        int findTargetSumWays_better(std::vector<int>& nums, int S){
            int size = nums.size();
            std::vector<int> dp_0(2000+5, 0);
            std::vector<int> dp_1(2000+5, 0);
            dp_0[ nums[0]+1000]  = 1;
            dp_0[-nums[0]+1000] += 1;
            for(int i=1; i<size; ++i){
                for(int j=-1000; j<=1000; ++j){
                    if(dp_0[j+1000]>0){
                        dp_1[j+1000-nums[i]] += dp_0[j+1000];
                        dp_1[j+1000+nums[i]] += dp_0[j+1000];
                    }
                }
                dp_0 = dp_1;
                fill(dp_1.begin(), dp_1.end(), 0);
            }
            return S>1000?0:dp_0[S+1000];
        }
//给你一个 m * n 的矩阵 mat 和一个整数 K ，请你返回一个矩阵 answer ，其中每个 answer[i][j] 是所有满足下述条件的元素 mat[r][c] 的和： 
//i - K <= r <= i + K, j - K <= c <= j + K 
//(r, c) 在矩阵内。
        std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>>& mat, int K){
            int size_i = mat.size();
            int size_j = mat[0].size();
            std::vector<std::vector<int>> dp(size_i, std::vector<int>(size_j, 0));
            dp[0].assign(mat[0].begin(), mat[0].end());
            for(int i=1; i<size_i; ++i)dp[i][0] = dp[i-1][0] + mat[i][0];
            for(int i=1; i<size_j; ++i)dp[0][i] = dp[0][i-1] + mat[0][i];
            for(int i=1; i<size_i; ++i){
                for(int j=1; j<size_j; ++j){
                    dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + mat[i][j];
                }
            }
            std::vector<std::vector<int>> res(size_i, std::vector<int>(size_j, 0));
            for(int i=0; i<size_i; ++i){
                int t_i_l = i-K>0?i-K:0;
                int t_i_r = i+K>=size_i?size_i-1:i+K;
                for(int j=0; j<size_j; ++j){
                    int t_j_l = j-K>0?j-K:0;
                    int t_j_r = j+K>=size_j?size_j-1:j+K;
                    if(!t_i_l && !t_j_l){
                        res[i][j] = dp[t_i_r][t_j_r];
                    }else if(!t_i_l){
                        res[i][j] = dp[t_i_r][t_j_r] - dp[t_i_r][t_j_l-1];
                    }else if(!t_j_l){
                        res[i][j] = dp[t_i_r][t_j_r] - dp[t_i_l-1][t_j_r];
                    }else{
                        res[i][j] = dp[t_i_r][t_j_r]   - dp[t_i_r][t_j_l-1] - 
                                    dp[t_i_l-1][t_j_r] + dp[t_i_l-1][t_j_l-1];
                    }
                }
            }
            return res;
        }
};

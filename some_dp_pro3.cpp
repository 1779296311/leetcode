/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_dp_pro3.cpp
*     author   : @ JY
*     date     : 2020--10--16
**********************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <bitset>
#include <unordered_map>
#include <cstring>
#include <unordered_set>
#include <stdlib.h>
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution{
    public:
//1405. 最长快乐字符串
        std::string longestDiversString(int a, int b, int c){
            std::vector<std::pair<int, char>> mp = {{a,'a'}, {b,'b'}, {c,'c'}};
            std::string res;
            int len = a + b + c;
            while(res.size() < len){
                std::sort(rbegin(mp), rend(mp));
                if(!res.size() || res.back() != mp[0].second){
                    if(--mp[0].first>=0)res += mp[0].second;
                    if(--mp[0].first>=0)res += mp[0].second;
                }else{
                    if(--mp[1].first>=0){
                        res += mp[1].second;
                    }else{
                        break;
                    }
                }
            }
            return res;
        }
//1043. 分隔数组以得到最大和
        int maxSumAfterParititioning(std::vector<int> &arr, int k){
            int len = arr.size();
            std::vector<int> dp(len);
            for(int i=0; i<len; ++i){
                int max_ = arr[i];
                for(int j=i; (i-j+1)<=k && j>=0; --j){
                    max_  = std::max(arr[j], max_);
                    dp[i] = std::max(dp[i], (j?dp[j-1]:0) + max_ * (i-j+1));
                }
            }
            return dp[len-1];
        }
        int maxSumAfterParititioning_other(std::vector<int> &arr, int k){
            int len = arr.size();
            std::vector<std::vector<int>> dp(k+1, std::vector<int>(len+1));
            for(int i=1; i<=k; ++i){
                for(int j=1; j<=len; ++j){
                    int max_ = arr[j-1];
                    for(int m=j; m>=i; --m){
                        max_ = std::max(max_, arr[m-1]);
                        dp[i][j] = std::max(dp[i][j], dp[i-1][m-1] + max_ * (j-m+1));
                        if(i==2 && j==5){
                            std::cout<<dp[i][j]<<"   "<<dp[i-1][m-1]<<"    "<<m<<"   "<<max_<<std::endl;;
                        }
                    }
                }
            }
            for(int i=0; i<=k; ++i){
                for(int j=0; j<=len; ++j){
                    std::cout<<dp[i][j]<<"   ";
                }
                std::cout<<std::endl;
            }
            return dp[k][len];
        }
//1012. 至少有 1 位重复的数字
        int numDupDigitsAtMostN(int N){
            std::vector<int> dig;
            int t = N;
            while(t){
                dig.push_back(t % 10);
                t /= 10;
            }
            int len = dig.size();
            int dp[len][(1<<10)];
            std::memset(dp, -1, sizeof dp);
            std::function<int(int, int, int, int)> _dfs
                = [&](int pos, int limit, int zero, int state){
                    if(pos==-1)return int(state>0);
                    if(!limit && !zero && dp[pos][state] != -1)return dp[pos][state];
                    int ans = 0;
                    int up  = limit ? dig[pos] : 9;
                    for(int i=0; i<=up; ++i){
                        if(state & (1<<i))continue;
                        ans += _dfs(pos-1, limit&&i==up, !i&&zero, state | ((zero && !i) ? 0 : (1<<i)));
                    }
                    return !limit&&!zero ? dp[pos][state] = ans : ans;
                };
            return N - _dfs(len-1, 1, 1, 0);

            //int len = dig.size();
            //int dp[len][(1<<10)][11];
            //std::memset(dp, -1, sizeof dp);
            //std::function<int(int, int, int, int, int)> _dfs
                //= [&](int pos, int limit, int zero, int state, int n){
                    //if(pos == -1)return int(n>0);
                    //if(!limit && !zero && dp[pos][state][n] != -1)return dp[pos][state][n];
                    //int ans = 0;
                    //int up  = limit ? dig[pos] : 9;
                    //for(int i=0; i<=up; ++i){
                        //int t = (state & (1<<i)) > 0;
                        //ans += _dfs(pos-1, limit&&i==up, zero&&!i, state | ((zero && !i) ? 0 : (1<<i)), n+t);
                    //}
                    //return !limit&&!zero ? dp[pos][state][n] = ans : ans;
                //};
            //return _dfs(len-1, 1, 1, 0, 0);
        }
//1373. 二叉搜索子树的最大键值和
        int maxSumBST(TreeNode *root){
            struct _node{
                bool is_ok;
                int sum_, max_, min_;
                _node(int i, int s, int l, int r) :
                    is_ok(i), sum_(s), max_(l), min_(r) {}
            };
            int res = 0;
            std::function<_node(TreeNode *)> _dfs = [&](TreeNode *root){
                if(!root)return _node{1, 0, INT_MIN, INT_MAX};
                _node left  = _dfs(root->left);
                _node right = _dfs(root->right);
                bool is_ok  = left.is_ok && right.is_ok &&
                              root->val > left.max_ &&
                              root->val < right.min_;
                int sum = root->val + left.sum_ + right.sum_;
                if(is_ok)res = std::max(res, sum);
                return _node{is_ok, sum,
                                std::max({root->val, right.max_, left.max_}),
                                std::min({root->val, right.min_, left.min_})};
            };
            _dfs(root);
            return res;
        }

//1335. 工作计划的最低难度
        int minDifficulty(std::vector<int> &jobDifficulty, int d){
            int len = jobDifficulty.size();
            if(d > len)return -1;
            if(d==len)return std::accumulate(begin(jobDifficulty), end(jobDifficulty), 0);
            std::vector<std::vector<int>> dp(d+1, std::vector<int>(len+1, 50000));
            dp[1][0] = 0, dp[1][1] = jobDifficulty[0];
            for(int i=2; i<=d; ++i)dp[1][i] = std::max(dp[1][i-1], jobDifficulty[i-1]);
            for(int i=1; i<=d; ++i){
                for(int j=1; j<=len; ++j){
                    int max_ = jobDifficulty[j-1];
                    for(int k=j; k>=i; --k){
                        max_ = std::max(max_, jobDifficulty[k-1]);
                        dp[i][j] = std::min(dp[i][j], dp[i-1][k-1] + max_);
                    }
                }
            }
            //for(int i=0; i<=d; ++i){
                //for(int j=1; j<=len; ++j){
                    //std::cout<<dp[i][j]<<"   ";
                //}
                //std::cout<<std::endl;
            //}
            return dp[d][len-1];
        }
//691. 贴纸拼词
        int minStickers(std::vector<std::string> &stickers, std::string target){
            std::unordered_set<char> cs;
            std::vector<int> wd(26);
            for(auto &c : target)cs.insert(c), ++wd[c-'a'];
            std::unordered_set<std::string> temp;
            std::string s;
            for(auto &v : stickers){
                for(auto &c : v)if(cs.count(c))s += c;
                if(!s.size())continue;
                std::sort(begin(s), end(s));
                temp.insert(s);
                s = "";
            }
            std::vector<std::string> t1(begin(temp), end(temp));
            std::unordered_set<int> del;
            for(int i=0; i<t1.size(); ++i){
                for(int j=0; j<t1.size(); ++j){
                    if(i==j)continue;
                    if(std::string::npos != t1[i].find(t1[j]))del.insert(j);
                }
            }
            std::vector<std::string> t2;
            for(int i=0; i<t1.size(); ++i){
                if(!del.count(i))t2.push_back(t1[i]);
            }
            std::vector<std::vector<int>> mp;
            for(auto &v : t2){
                std::vector<int> t3(26);
                for(auto &c : v)++t3[c-'a'];
                mp.push_back(t3);
            }
            int len = target.size(), n = mp.size(), INF = 1e8;
            std::vector<int> dp((1<<len), INF);
            dp[0] = 0;
            for(int i=0; i<(1<<len); ++i){
                if(dp[i] == INF)continue;
                for(int j=0; j<n; ++j){
                    int state = i;
                    auto left = mp[j];
                    for(int k=0; k<len; ++k){
                        if(state & (1<<k))continue;
                        if(--left[target[k]-'a']>=0)state |= (1<<k);
                    }
                    dp[state] = std::min(dp[state], dp[i] + 1);
                }
            }
            return dp[(1<<len)-1] == INF ? -1 : dp[(1<<len)-1];
        }
        int minStickers_fuck(std::vector<std::string> &stickers, std::string target){
            std::unordered_set<char> cs;
            std::vector<int> wd(26);
            for(auto &c : target)cs.insert(c), ++wd[c-'a'];
            std::unordered_set<std::string> temp;
            std::string s;
            for(auto &v : stickers){
                for(auto &c : v)if(cs.count(c))s += c;
                if(!s.size())continue;
                std::sort(begin(s), end(s));
                temp.insert(s);
                s = "";
            }
            std::vector<std::string> t1(begin(temp), end(temp));
            std::unordered_set<int> del;
            for(int i=0; i<t1.size(); ++i){
                for(int j=0; j<t1.size(); ++j){
                    if(i==j)continue;
                    if(std::string::npos != t1[i].find(t1[j]))del.insert(j);
                }
            }
            std::vector<std::string> t2;
            for(int i=0; i<t1.size(); ++i){
                if(!del.count(i))t2.push_back(t1[i]);
            }
            std::vector<std::vector<int>> mp;
            for(auto &v : t2){
                std::vector<int> t3(26);
                for(auto &c : v)++t3[c-'a'];
                mp.push_back(t3);
            }
            int res = INT_MAX;
            std::function<void(std::vector<int>&, int)> _dfs
                    = [&](std::vector<int> &dig, int n){
                        if(*max_element(begin(dig), end(dig)) <= 0){
                            res = std::min(res ,n);
                            return;
                        }
                        int index = 0;
                        while(dig[index]<=0)++index;
                        for(auto &v : mp){
                            if(v[index]){
                                for(auto c : cs)dig[c-'a'] -= v[c-'a'];
                                _dfs(dig, n+1);
                                for(auto c : cs)dig[c-'a'] += v[c-'a'];
                            }
                        }
                };
            _dfs(wd, 0);
            return res==INT_MAX ? -1 : res;
        }

//600. 不含连续1的非负整数
        int findIntegers(int num){
            std::vector<int> dig;
            int temp = num;
            while(temp){
                dig.push_back(temp & 1);
                temp >>= 1;
            }
            int len = dig.size();
            std::vector<std::vector<int>> dp(len, std::vector<int>(2, -1));
            std::function<int(int, int, int)> _dfs
                    = [&](int pos, int pre, int limit){
                        if(pos==-1)return 1;
                        if(!limit && dp[pos][pre] != -1)return dp[pos][pre];
                        int ans = 0;
                        int up = limit ? dig[pos] : 1;
                        for(int i=0; i<=up; ++i){
                            if(pre && i)continue;
                            ans += _dfs(pos-1, i, limit&&i==up);
                        }
                        return !limit ? dp[pos][pre] = ans : ans;
                };
            return _dfs(len-1, 0, 1);
        }

//面试题 16.17. 连续数列
        int maxSubarray(std::vector<int> &nums){
            int cur = 0, pre = 0, len = nums.size(), res = INT_MIN;
            for(int i=0; i<len; ++i){
                cur = nums[i];
                if(pre > 0)cur += pre;
                pre = cur;
                res = std::max(res, cur);
            }
            return res;
        }
//698. 划分为k个相等的子集
        bool conPartitionKSubsets_dfs(std::vector<int> &nums, int k){
            int sum = std::accumulate(begin(nums), end(nums), 0);
            if(sum % k)return false;
            int target = sum / k;
            int len = nums.size();
            std::vector<int> vi(len);
            std::function<bool(int, int, int)> _dfs
                = [&](int cur, int k, int sum){
                    if(k==1)return true;
                    for(int i=cur; i<len; ++i){
                        int temp = nums[i] + sum;
                        if(vi[i] || temp > target)continue;
                        vi[i] = 1;
                        if(temp==target && _dfs(0, k-1, 0))return true;
                        if(temp<target && _dfs(i+1, k, temp))return true;
                        vi[i] = 0;
                    }
                    return false;
                };
            return _dfs(0, k, 0);
        }
        bool conPartitionKSubsets(std::vector<int> &nums, int k){
            int sum = std::accumulate(begin(nums), end(nums), 0);
            if(sum % k)return false;
            sum /= k;
            std::sort(begin(nums), end(nums));
            if(nums.back() > sum)return false;
            int len = nums.size();
            std::vector<int> dp(1<<len), sums(1<<len);
            dp[0] = 1;
            for(int state=0; state<(1<<len); ++state){
                if(!dp[state])continue;
                for(int i=0; i<len; ++i){
                    if(state & (1<<i))continue;
                    if(dp[state | (1<<i)])continue;
                    if((sums[state]%sum) + nums[i] <= sum){
                        dp[state|(1<<i)] = 1;
                        sums[state|(1<<i)] = nums[i] + sums[state];
                    }else{
                        break;
                    }
                }
            }
            return dp[(1<<len)-1];
        }
//764. 最大加号标志
        int orderOfLargestPlusSign(int N, std::vector<std::vector<int>> &mines){
            std::vector<std::vector<int>> left(N, std::vector<int>(N)), right(N, std::vector<int>(N)),
                                          down(N, std::vector<int>(N)), up(N, std::vector<int>(N));
            int mp[N][N];
            memset(mp, 0, sizeof mp);
            for(auto &p : mines)mp[p[0]][p[1]] = 1;
            for(int i=0; i<N; ++i){
                for(int j=0; j<N; ++j){
                    if(mp[i][j])continue;
                    left[i][j] = up[i][j] = 1;
                    if(j)left[i][j] += left[i][j-1];
                    if(i)up[i][j] += up[i-1][j];
                }
            }
            for(int i=N-1; i>=0; --i){
                for(int j=N-1; j>=0; --j){
                    if(mp[i][j])continue;
                    right[i][j] = down[i][j] = 1;
                    if(j<N-1)right[i][j] += right[i][j+1];
                    if(i<N-1)down[i][j] += down[i+1][j];
                }
            }
            int res = 0;
            for(int i=0; i<N; ++i){
                for(int j=0; j<N; ++j){
                    if(mp[i][j])continue;
                    res = std::max(res, std::min({left[i][j], right[i][j], up[i][j], down[i][j]}));
                }
            }
            return res;
        }
//1420. 生成数组
        int numOfArrays(int n, int m, int k){
            int MOD = 1e9 + 7;
            long long dp[n+1][m+2][k+2];
            std::memset(dp, 0, sizeof dp);
            dp[0][0][0] = 1;
            for(int i=1; i<=n; ++i){
                for(int j=0; j<=m; ++j){
                    for(int z=1; z<=k; ++z){
                        for(int y=1; y<=m; ++y){
                            if(y > j){
                                dp[i][y][z] = (dp[i][y][z] + dp[i-1][j][z-1]) % MOD;
                            }else{
                                dp[i][j][z] = (dp[i][j][z] + dp[i-1][j][z]) % MOD;
                            }
                        }
                    }
                }
            }
            long long res = 0;
            for(int i=1; i<=m; ++i){
                res = (res + dp[n][i][k]) % MOD;
            }
            return res;
        }
        int numOfArrays_SW(int n, int m, int k){
            int MOD = 1e9 + 7;
            int dp[51][101][k+2];
            std::memset(dp, -1, sizeof dp);
            std::function<int(int, int, int)> _dfs = [&](int pos, int max_, int kt){
                if(!pos)return int(k == kt);
                if(kt > k)return 0;
                if(dp[pos][max_][kt] != -1)return dp[pos][max_][kt];
                int ans = 0;
                for(int i=1; i<=m; ++i){
                    if(i > max_){
                        ans = (ans + _dfs(pos-1, i, kt+1)) % MOD;
                    }else{
                        ans = (ans + _dfs(pos-1, max_, kt)) % MOD;
                    }
                }
                return dp[pos][max_][kt] = ans;
            };
            return _dfs(n, 0, 0);
        }
//1186. 删除一次得到子数组最大和
        int maxiumSum(std::vector<int> &arr){
            int len = arr.size();
            std::vector<int> left(arr), right(arr);
            int res = std::max(left[0], right.back());
            for(int i=1; i<len; ++i){
                left[i] += std::max(left[i-1], 0);
                right[len-i-1] += std::max(right[len-i], 0);
                res = std::max({res, left[i], right[len-i-1]});
            }
            for(int i=1; i<len-1; ++i){
                res = std::max(res, left[i-1] + right[i+1]);
            }
            return res;
        }

//1269. 停在原地的方案数
        int numWays_better(int steps, int arrLen){
            int MOD = 1e9 + 7;
            arrLen = std::min(steps+1, arrLen);
            std::vector<long long> dp_0(arrLen+1), dp_1(arrLen+1);
            dp_0[0] = 1;
            for(int i=1; i<=steps; ++i){
                for(int j=0; j<arrLen; ++j){
                    dp_1[j] = (dp_0[j] + dp_0[j+1]) % MOD;
                    if(j)dp_1[j] = (dp_1[j] + dp_0[j-1]) % MOD;
                }
                dp_0 = dp_1;
            }
            return dp_0[0];
        }
        int numWays(int steps, int arrLen){
            int MOD = 1e9 + 7;
            arrLen  = std::min(steps+1, arrLen);
            std::vector<std::vector<long long>> dp(steps+1, std::vector<long long>(arrLen+1));
            dp[0][0] = 1;
            for(int i=1; i<=steps; ++i){
                for(int j=0; j<arrLen; ++j){
                    dp[i][j] = (dp[i-1][j] + dp[i-1][j+1]) % MOD;
                    if(j)dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % MOD;
                }
            }
            return dp[steps][0];
        }
//920. 播放列表的数量
        int numMusicPlaylists(int N, int L, int K){
            int MOD = 1e9 + 7;
            std::vector<std::vector<long long>> dp(N+1, std::vector<long long>(L+1));
            dp[0][0] = 1;
            for(int i=1; i<=N; ++i){
                for(int j=1; j<=L; ++j){
                    dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (N-i+1)) % MOD;
                    dp[i][j] = (dp[i][j] + dp[i][j-1] * std::max(0, i-K)) % MOD;
                }
            }
            return dp[N][L];
            //std::vector<std::vector<long long>> dp(L+1, std::vector<long long>(N+1));
            //dp[0][0] = 1;
            //for(int i=1; i<=L; ++i){
                //for(int j=1; j<=N; ++j){
                    //dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (N-j+1)) % MOD;
                    //dp[i][j] = (dp[i][j] + dp[i-1][j] * std::max(0, j-K)) % MOD;
                //}
            //}
            //return dp[L][N];
        }
//486. 预测赢家
        bool PredictTheWinner(std::vector<int> &nums){
            int len = nums.size();
            std::vector<std::vector<int>> dp(len, std::vector<int>(len));
            for(int j=0; j<len; ++j){
                for(int i=j; i>=0; --i){
                    if(i==j){
                        dp[i][j] = nums[i];
                        continue;
                    }
                    dp[i][j] = std::max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
                }
            }
            return dp[0][len-1] >= 0;
        }
//1027. 最长等差数列
        int longestArithSeqLength(std::vector<int> &A){
            int len = A.size(), res = 0;
            std::vector<std::vector<int>> dp(len, std::vector<int>(len, 2));
            std::unordered_map<int, int> mp;
            mp[A[0]] = 0;
            for(int i=1; i<len-1; ++i){
                for(int j=i+1; j<len; ++j){
                    int target = A[i] * 2 - A[j];
                    if(target < 0)continue;
                    if(mp.count(target))dp[i][j] = dp[mp[target]][i] + 1;
                    res = std::max(res, dp[i][j]);
                }
                mp[A[i]] = i;
            }
            return res;
        }
//712. 两个字符串的最小ASCII删除和
        int minimumDeleteSun_better(std::string s1, std::string s2){
            int len1 = s1.size(), len2 = s2.size();
            std::vector<std::vector<int>> dp(len1+1, std::vector<int>(len2+1));
            for(int i=1; i<=len1; ++i)dp[i][0] = dp[i-1][0] + s1[i-1];
            for(int i=1; i<=len2; ++i)dp[0][i] = dp[0][i-1] + s2[i-1];
            for(int i=1; i<=len1; ++i){
                for(int j=1; j<=len2; ++j){
                    dp[i][j] = std::min(dp[i-1][j] + s1[i-1], dp[i][j-1] + s2[j-1]);
                    if(s1[i-1] == s2[j-1])dp[i][j] = std::min(dp[i][j], dp[i-1][j-1]);
                }
            }
            return dp[len1][len2];
        }
        int minimumDeleteSun(std::string s1, std::string s2){
            int len1 = s1.size(), len2 = s2.size();
            std::vector<std::vector<int>> dp(len1, std::vector<int>(len2, 1001));
            int sum = 0, f = 1;
            for(int i=0; i<len1; ++i){
                sum += s1[i];
                if(s2[0] == s1[i]){
                    dp[i][0] = sum - s2[0];
                    f = -1;
                }else{
                    dp[i][0] = f * s2[0] + sum;
                }
            }
            sum = 0, f = 1;
            for(int i=0; i<len2; ++i){
                sum += s2[i];
                if(s2[i] == s1[0]){
                    dp[0][i] = sum - s1[0];
                    f = -1;
                }else{
                    dp[0][i] = f * s1[0] + sum;
                }
            }
            for(int i=1; i<len1; ++i){
                for(int j=1; j<len2; ++j){
                    dp[i][j] = std::min(dp[i-1][j] + s1[i], dp[i][j-1] + s2[j]);
                    if(s1[i] == s2[j]){
                        dp[i][j] = std::min(dp[i][j], dp[i-1][j-1]);
                    }
                }
            }
            return dp[len1-1][len2-1];
        }
//1363. 形成三的最大倍数
        std::string LargestMultipleOfThree(std::vector<int> &digits){
            std::vector<int> cnt(10);
            int sum = 0;
            for(auto &x : digits)++cnt[x], sum += x;
            std::function<bool(int)> _del = [&](int m){
                    for(int i=m; i<=9; i+= 3){
                        if(cnt[i] > 0){
                            --cnt[i];
                            return 1;
                        }
                    }
                    return 0;
                };
            if(sum%3==1 && !_del(1)) _del(2), _del(2);
            if(sum%3==2 && !_del(2)) _del(1), _del(1);
            std::string res;
            for(int i=9; i>=0; --i){
                while(cnt[i]--)res += i + '0';
            }
            if(res.size() && res.size()=='0')return "0";
            return res;
        }

//1220. 统计元音字母序列的数目
        int countVowelPermutation(int n){
            int MOD = 1e9 + 7;
            std::vector<std::vector<long long>> dp(n, std::vector<long long>(5, 0));
            for(int i=0; i<5; ++i)dp[0][i] = 1;
            for(int i=1; i<n; ++i){
                dp[i][0] = (dp[i-1][1] + dp[i-1][2] + dp[i-1][4]) % MOD;
                dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % MOD;
                dp[i][2] = (dp[i-1][1] + dp[i-1][3]) % MOD;
                dp[i][3] = (dp[i-1][2]) % MOD;
                dp[i][4] = (dp[i-1][3] + dp[i-1][2]) % MOD;
            }
            int res = 0;
            for(auto &x : dp[n-1])res = (res + x) % MOD;
            return res;
        }
//903. DI 序列的有效排列
        int numPermDISequence(std::string &S){
            int n = S.size(), MOD = 1e9 + 7;
            std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, 0));
            dp[0][0] = 1;
            for(int i=1; i<=n; ++i){
                if(S[i-1] == 'D'){
                    for(int j=i-1; j>=0; --j){
                        dp[i][j] = (dp[i][j+1] + dp[i-1][j]) % MOD;
                    }
                }else{
                    for(int j=1; j<=i; ++j){
                        dp[i][j] = (dp[i-1][j-1] + dp[i][j-1]) % MOD;
                    }
                }
                //for(int j=0; j<=i; ++j){
                    //if(S[i-1] == 'D'){
                        //for(int k=j; k<i; ++k){
                            //dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD;
                        //}
                    //}else{
                        //for(int k=0; k<j; ++k){
                            //dp[i][j] = (dp[i][j] + dp[i-1][k]) % MOD;
                        //}
                    //}
                //}
            }
            int res = 0;
            for(auto &x : dp[n])res = (res + x) % MOD;
            return res;
        }
//1278. 分割回文串 III
        int palindromePartition(std::string s, int k){
            int len = s.size();
            if(k>=len)return 0;
            std::vector<std::vector<int>> mp(len, std::vector<int> (len, len));
            for(int j=0; j <len; ++j){
                for(int i=j; i>=0; --i){
                    if(j==i){
                        mp[i][j] = 0;
                        continue;
                    }
                    if(j-i==1){
                        mp[i][j] = s[i] != s[j];
                        continue;
                    }
                    mp[i][j] = std::min(mp[i][j], mp[i+1][j-1]+(s[i]!=s[j]));
                }
            }
            std::vector<int> dp_0(len, len), dp_1(len, len);
            for(int i=0; i<len; ++i)dp_0[i] = mp[0][i];
            for(int i=1; i<k; ++i){
                for(int j=i; j<len; ++j){
                    for(int m=i; m<j; ++m){
                        dp_1[j] = std::min(dp_1[j], dp_0[m] + mp[m+1][j]);
                    }
                }
                dp_0 = dp_1;
                std::fill(begin(dp_1), end(dp_1), len);
            }
            //std::vector<std::vector<int>> dp(k, std::vector<int>(len, len));
            //for(int i=0; i<len; ++i)dp[0][i] = mp[0][i];
            //for(int i=1; i<k; ++i){
                //for(int j=i; j<len; ++j){
                    //for(int m=i-1; m<j; ++m){
                        //dp[i][j] = std::min(dp[i][j], dp[i-1][m] + mp[m+1][j]);
                    //}
                //}
            //}
            return dp_0[len-1];
        }
//943. 最短超级串
        std::string shoarestSuperstring(std::vector<std::string> &A){
            int len = A.size();
            std::vector<std::vector<int>> dis(len, std::vector<int>(len));
            for(int i=0; i<len; ++i){
                for(int j=0; j<len; ++j){
                    if(i == j)continue;
                    for(int l=std::min(A[i].size(), A[j].size()); l>0; --l){
                        if(A[i].substr(A[i].size() - l, l) == A[j].substr(0, l)){
                            dis[i][j] = l;
                            break;
                        }
                    }
                }
            }
            int all = 1 << len;
            std::vector<std::vector<int>> dp(all, std::vector<int>(len, INT_MAX));
            std::vector<std::vector<int>> parent(all, std::vector<int>(len));
            for(int i=0; i<len; ++i)dp[1<<i][i] = A[i].size();
            for(int state=0; state<all; ++state){
                for(int i=0; i<len; ++i){
                    if(!(state & (1<<i)))continue;
                    for(int j=0; j<len; ++j){
                        if(i == j)continue;
                        if(state & (1<<j))continue;
                        int temp = dp[state][i] + A[j].size() -  dis[i][j];
                        if(temp < dp[state|(1<<j)][j]){
                            dp[state|(1<<j)][j] = temp;
                            parent[state|(1<<j)][j] = i;
                        }
                    }
                }
            }
            int last = std::min_element(begin(dp[all-1]), end(dp[all-1])) - begin(dp[all-1]);
            std::vector<int> path {last};
            int t = all - 1, i = 0;
            while(++i<len){
                int k = last;
                last  = parent[t][last];
                path.push_back(last);
                t ^=  (1<<k);
            }
            std::reverse(begin(path), end(path));
            std::string res = A[path[0]];
            for(int i=1; i<len; ++i){
                res += A[path[i]].substr(dis[path[i-1]][path[i]]);
            }
            return res;
        }

//1024. 视频拼接
        int viedoStitching(std::vector<std::vector<int>> &clips, int T){
            int len = clips.size();
            std::vector<int> dp(1001, 0);
            for(auto &v : clips){
                dp[v[0]] = std::max(dp[v[0]], v[1]);
            }
            int mx = 0, r = 0, res = 0;
            for(int i=0; i<T; ++i){
                mx = std::max(mx, dp[i]);
                if(i==r){
                    ++res;
                    r = mx;
                }
                if(i==mx)return -1;
            }
            return res;
        }
//1449. 数位成本和为目标值的最大数字
        std::string largestNumber(std::vector<int> &cost, int target){
            std::function<bool(std::string &, std::string &)> _cmp_str
                = [&](std::string &s1, std::string &s2){
                    return s1.size() == s2.size() ? s1 > s2 : s1.size() > s2.size();
                };
            int len = cost.size();
            std::vector<std::string> dp(target+1, "*");
            dp[0] = "";
            for(int i=0; i<len; ++i){
                for(int j=cost[i]; j<=target; ++j){
                    if(dp[j-cost[i]] != "*"){
                        std::string s1 = std::to_string(i+1) + dp[j-cost[i]];
                        if(dp[j]=="*" || _cmp_str(s1, dp[j])){
                            dp[j] = s1;
                        }
                    }
                }
            }
            return dp.back()=="*" ? "0" : dp.back();
        }
//1143. 最长公共子序列
        int longestCommonSubSeqence(std::string text1, std::string text2){
            if(text1.size() < text2.size())std::swap(text1, text2);
            int len1 = text1.size(), len2 = text2.size();
            std::vector<int> dp(len2, 0);
            for(int i=0; i<len1; ++i){
                int pre = 0, temp;
                for(int j=0; j<len2; ++j){
                    temp = dp[j];
                    if(j>0)dp[j] = std::max(dp[j], dp[j-1]);
                    if(text1[i]==text2[j])dp[j] = std::max(dp[j], pre+1);
                    pre = temp;
                }
            }
            return dp[len2-1];
        }
//1301. 最大得分的路径数目
        std::vector<int> pathsWithMaxScore(std::vector<std::string> &board){
            using ll    = long long;
            using pllll = std::pair<ll,ll>;
            int MOD     = 1e9 + 7;
            int m = board.size(), n = board[0].size();
            board[m-1][n-1] = board[0][0] = '0';
            std::vector<std::vector<pllll>> dp(m, std::vector<pllll>(n, {-1, -1}));
            dp[m-1][n-1] = {0, 1};
            std::function<void(int, int, int, int)> _update = [&](int i, int j, int pi, int pj){
                if(pi>=m || pj>=n || dp[pi][pj].first == -1)return;
                auto &&[af, as] = dp[i][j];
                auto &&[pf, ps] = dp[pi][pj];
                if(af < pf){
                    af = pf, as = ps;
                }else if(af==pf){
                    as = (as + ps) % MOD;
                }
            };
            for(int i=m-1; i>=0; --i){
                for(int j=n-1; j>=0; --j){
                    if(board[i][j] == 'X')continue;
                    _update(i, j, i+1, j);
                    _update(i, j, i, j+1);
                    _update(i, j, i+1, j+1);
                    dp[i][j].first = (dp[i][j].first + board[i][j] - '0') % MOD;
                }
            }
            using vi = std::vector<int>;
            auto [ansf, anss] = dp[0][0];
            return ansf==-1 || anss==-1 ? vi{0, 0} : vi{(int)ansf % MOD, (int)anss% MOD};
        }
        std::vector<int> pathsWithMaxScore_fuck(std::vector<std::string> &board){
            using ll = long long;
            int m = board.size(), n = board[0].size();
            std::vector<std::vector<ll>> dp_1(m, std::vector<ll>(n, -1));
            dp_1[m-1][n-1] = 0;
            board[m-1][n-1] = board[0][0] = '0';
            for(int i=m-1; i>=0; --i){
                for(int j=n-1; j>=0; --j){
                    if(board[i][j]=='X')continue;
                    int val = board[i][j] - '0';
                    if(i<m-1 && dp_1[i+1][j] != -1){
                        dp_1[i][j] = std::max<ll>(dp_1[i][j], dp_1[i+1][j] + val);
                    }
                    if(j<n-1 && dp_1[i][j+1] != -1){
                        dp_1[i][j] = std::max<ll>(dp_1[i][j], dp_1[i][j+1] + val);
                    }
                    if(j<n-1 && i<m-1 && dp_1[i+1][j+1] != -1){
                        dp_1[i][j] = std::max<ll>(dp_1[i][j], dp_1[i+1][j+1] + val);
                    }
                }
            }
            int MOD = 1e9 + 7;
            ll max_ = dp_1[0][0], num_ = 0;
            if(max_ == -1)return {0, 0};
            std::function<ll(int, int, ll)> _dfs = [&](int i, int j, ll sum){
                if(i<0 || j<0 || board[i][j]=='X')return (ll)0;
                if(!i && !j && sum==max_){
                    return (ll)1;
                }
                int val = board[i][j] - '0';
                ll ans  = _dfs(i-1, j, sum + val) +
                          _dfs(i, j-1, sum + val) +
                          _dfs(i-1, j-1, sum + val);
                return ans;
            };
            num_ = _dfs(m-1, n-1, 0);
            return {int(max_ % MOD), int(num_ % MOD)};
        }
//面试题 17.23. 最大黑方阵
        std::vector<int> findSquare(std::vector<std::vector<int>> &matrix){
            int m = matrix.size(), n = matrix[0].size();
            std::vector<std::vector<int>> row(matrix), col(matrix);
            for(int i=0; i<m; ++i){
                row[i][0] = !matrix[i][0];
                for(int j=1; j<n; ++j){
                    row[i][j] = !matrix[i][j] ? row[i][j-1] + 1 : 0;
                }
            }
            for(int j=0; j<n; ++j){
                col[0][j] = !matrix[0][j];
                for(int i=1; i<m; ++i){
                    col[i][j] = !matrix[i][j] ? col[i-1][j] + 1 : 0;
                }
            }
            std::vector<int> res = {0, 0, -1};
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    if(matrix[i][j])continue;
                    int len = std::min(row[i][j], col[i][j]);
                    while(len>0){
                        int i1 = i - len + 1;
                        int j1 = j - len + 1;
                        if(row[i1][j] >= len && col[i][j1] >= len && len > res[2]){
                            res[0] = i1, res[1] = j1, res[2] = len;
                            break;
                        }
                        --len;
                    }
                }
            }
            return res[2]==-1 ? std::vector<int>{} : res;
        }
//1326. 灌溉花园的最少水龙头数目
        int minTaps(int n, std::vector<int> &ranges){
            std::vector<int> dp(n+1, n+1);
            for(int i=0; i<=n; ++i){
                if(!ranges[i])continue;
                int l = std::max(0, i - ranges[i]);
                int r = std::min(n, i + ranges[i]);
                int m = !l ? 0 : dp[l];
                if(m==n-1)continue;
                for(int j=l; j<=r; ++j){
                    dp[j] = std::min(dp[j], m + 1);
                }
            }
            return dp[n] == n+1 ? -1 : dp[n];
        }
        int minTaps_fuck(int n, std::vector<int> &ranges){
            std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, n));
            for(int j=0; j<=n; ++j){
                for(int i=j; i>=0; --i){
                    if(i==j){
                        dp[i][j] = 1;
                        continue;
                    }
                    for(int k=i; k<j; ++k){
                        int l = 0, r = 0, len = ranges[k];
                        if(k-len > i)l = dp[i][k-len];
                        if(k+len < j)r = dp[k+len][j];
                        dp[i][j] = std::min(dp[i][j], l+r+1);
                    }
                }
            }
            return dp[0][n]==n+1 ? -1 : dp[0][n];
        }
//982. 按位与为零的三元组
        int countTriplets(std::vector<int> &A){
            std::unordered_map<int, int> mp_1;
            int len = A.size(), res = 0;
            for(int i=0; i<len; ++i){
                ++mp_1[A[i]];
                for(int j=0; j<i; ++j){
                    mp_1[A[i] & A[j]] += 2;
                }
            }
            for(auto &&[k, v] : mp_1){
                for(auto x : A){
                    if(!(x & k))res += v;
                }
            }
            return res;
        }
//1397. 找到所有好字符串
        int findGoodStrings(int n, std::string s1, std::string s2, std::string evil){
            int MOD = 1e9 + 7;
            int len = evil.size();
            std::function<std::vector<int>(std::string &)> _get_next
                = [&](std::string &s){
                    std::vector<int> _next(len+2);
                    int i = 1, jump = 0;
                    while(i<len){
                        if(s[i] == s[jump]){
                            _next[++i] = ++jump;
                        }else if(!jump){
                            _next[++i] = 0;
                        }else{
                            jump = _next[jump];
                        }
                    }
                    return _next;
                };
            std::vector<int> next = _get_next(evil);
            std::vector<std::vector<int>> trans(len+3, std::vector<int>(26, -1));
            std::function<int(int, char)> _get_stats
                = [&](int stats, char now){
                    auto &ans = trans[stats][now-'a'];
                    if(ans != -1)return ans;
                    while(stats && evil[stats] != now)stats = next[stats];
                    return ans = (evil[stats]==now ? stats+1 : 0);
                };
            using vi  = std::vector<int>;
            using vvi = std::vector<vi>;
            vvi dp(n, vi(len+2, -1));
            std::function<int(int, int, int, std::string &)> _dfs
                = [&](int pos, int stats, int limit, std::string &s){
                    if(stats == len)return 0;
                    if(pos == n)return 1;
                    int ans = dp[pos][stats];
                    if(!limit && ans != -1)return ans;
                    ans = 0;
                    int r = (limit ? s[pos] : 'z');
                    for(int c='a'; c<=r; ++c){
                        ans = (ans + _dfs(pos+1, _get_stats(stats, c), limit&&c==s[pos], s)) % MOD;
                    }
                    if(!limit)dp[pos][stats] = ans;
                    return ans;
                };
            --s1[n-1];
            return (_dfs(0, 0, 1, s2) - _dfs(0, 0, 1, s1) + MOD) % MOD;
        }

//517. 超级洗衣机
        int findMinMoves(std::vector<int> &machines){
            int sum = std::accumulate(begin(machines), end(machines), 0);
            if(sum % machines.size())return -1;
            int k   = sum / machines.size();
            int res = 0, prefix = 0;
            for(auto &x : machines){
                prefix += (x -= k);
                res = std::max(res, std::max(abs(prefix), x));
            }
            return res;
        }
//1444. 切披萨的方案数
        int ways(std::vector<std::string> &pizza, int k){
            using ll   = long long;
            using vi   = std::vector<ll>;
            using vvi  = std::vector<vi>;
            using vvvi = std::vector<vvi>;
            int MOD = 1e9 + 7;
            int m = pizza.size(), n = pizza[0].size();
            vvi sums(m+1, vi(n+1));
            for(int i=1; i<=m; ++i){
                for(int j=1; j<=n; ++j){
                    sums[i][j] = ('A'==pizza[i-1][j-1]) + sums[i-1][j] +
                                 sums[i][j-1] - sums[i-1][j-1];
                }
            }
            std::function<bool(int, int, int, int)> _is_ok
                = [&](int si, int sj, int ei, int ej){
                    return sums[ei+1][ej+1] - sums[ei+1][sj] -
                           sums[si][ej+1] + sums[si][sj] > 0;
                };
            vvvi dp(m, vvi(n, vi(k+1)));
            dp[0][0][1] = 1;
            for(int x=2; x<=k; ++x){
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        if(!dp[i][j][x-1])continue;
                        for(int z=i+1; z<m; ++z){
                            if(_is_ok(i, j, z-1, n-1) &&
                                    _is_ok(z, j, m-1, n-1)){
                                dp[z][j][x] = (dp[z][j][x] + dp[i][j][x-1]) % MOD;
                            }
                        }
                        for(int z=j+1; z<n; ++z){
                            if(_is_ok(i, j, m-1, z-1) &&
                                    _is_ok(i, z, m-1, n-1)){
                                dp[i][z][x] = (dp[i][z][x] + dp[i][j][x-1]) % MOD;
                            }
                        }
                    }
                }
            }
            ll res = 0;
            for(int i=0; i<m; ++i){
                for(int j=0; j<n; ++j){
                    res += dp[i][j][k];
                }
            }
            return res % MOD;
        }
//面试题 17.24. 最大子矩阵
        std::vector<int> getMatrix(std::vector<std::vector<int>> &matrix){
            int m = matrix.size(), n = matrix[0].size();
            std::vector<int> sums(n), res(4);
            int max_ = INT_MIN;
            for(int i=0; i<m; ++i){
                for(auto &x : sums)x = 0;
                for(int k=i; k<m; ++k){
                    int sum = 0, bi, bj;
                    for(int j=0; j<n; ++j){
                        sums[j] += matrix[k][j];
                        if(sum > 0){
                            sum += sums[j];
                        }else{
                            sum  = sums[j];
                            bi = i, bj = j;
                        }
                        if(sum > max_){
                            max_ = sum;
                            res[0] = bi, res[1] = bj;
                            res[2] = k,  res[3] = j;
                        }
                    }
                }
            }
            return res;
        }
//1049. 最后一块石头的重量 II
        int lastStoneWeightII(std::vector<int> &stones){
            int sum = std::accumulate(begin(stones), end(stones), 0);
            std::vector<int> dp(sum/2 + 1);
            for(auto &s : stones){
                for(int j=sum/2; j>=s; --j){
                    dp[j] = std::max(dp[j], dp[j-s] + s);
                }
            }
            return sum - dp.back() * 2;
        }
//1359. 有效的快递序列数目
        int countOrders(int n){
            int MOD = 1e9 + 7;
            int res = 1;
            for(int i=2; i<=n; ++i){
                long long a = 2*(i-1) + 1;
                long long b = a*(a-1) / 2 + a;
                res = (res * b) % MOD;
            }
            return res;
        }
//1262. 可被三整除的最大和
        int maxSumDivThree(std::vector<int> &nums){
            std::vector<int> dp_0 = {0, INT_MIN, INT_MIN};
            std::vector<int> dp_1 = {0, INT_MIN, INT_MIN};
            for(auto &x : nums){
                for(int i=0; i<3; ++i){
                    dp_1[(x+i)%3] = std::max(dp_0[(x+i)%3], dp_0[i] + x);
                }
                dp_0 = dp_1;
            }
            return dp_0[0];
        }
//650. 只有两个键的键盘
        int minSteps(int n){
            std::vector<int> dp(n+1);
            std::iota(begin(dp)+2, end(dp), 2);
            for(int i=2; i<=n; ++i){
                for(int j=2*i; j<=n; j += i){
                    dp[j] = std::min(dp[j], dp[i] + j / i);
                }
            }
            return dp[n];
        }
//1147. 段式回文
        int longestDecompsition(std::string text){
            int res = 0;
            int pre = 0, len = text.size();
            for(int i=0; i<len / 2; ++i){
                if(text.substr(pre, i-pre+1) == text.substr(len-i-1, i-pre+1)){
                    res += 2;
                    pre  = i + 1;
                }
            }
            return res + (len&1 || pre < len / 2);
        }

//467. 环绕字符串中唯一的子字符串
        int findSubstringInWraproundString(std::string p){
            std::function<bool(char , char )> _is_ok = [&](char pre, char cur){
                return pre=='z' ? cur=='a' : (pre+1==cur); };
            std::vector<int> dp(26);
            int len = p.size(), k = 0;
            for(int i=0; i<len; ++i){
                if(i>0 && _is_ok(p[i-1], p[i])){
                    ++k;
                }else{
                    k = 1;
                }
                dp[p[i] - 'a'] = std::max(dp[p[i] - 'a'], k);
            }
            return std::accumulate(begin(dp), end(dp), 0);
        }
//321. 拼接最大数
        std::vector<int> maxNumber(std::vector<int> &nums1, std::vector<int> &nums2, int k){
            std::function<std::vector<int>(std::vector<int> &, int)> _maxk
                = [&](std::vector<int> &nums, int k){
                    int remain = nums.size() - k;
                    std::vector<int> res;
                    for(auto &x : nums){
                        while(res.size() && res.back() < x && remain-- > 0){
                            res.pop_back();
                        }
                        res.push_back(x);
                    }
                    res.resize(k);
                    return res;
                };
            std::vector<int> res;
            int len1 = nums1.size(), len2 = nums2.size();
            for(int s=std::max(0, k-len2); s<=std::min(len1, k); ++s){
                std::vector<int> temp;
                std::vector<int> max1 = _maxk(nums1, s);
                std::vector<int> max2 = _maxk(nums2, k - s);
                auto it1 = max1.begin(), it2 = max2.begin();
                while(it1 != end(max1) || it2!=end(max2)){
                    temp.push_back(std::lexicographical_compare(it1, end(max1), it2, end(max2)) ? *it2++ : *it1++);
                }
                res = std::max(res, temp);
            }
            return res;
        }
//1458. 两个子序列的最大点积
        int maxDotProduct(std::vector<int> &nums1, std::vector<int> &nums2){
            int len1 = nums1.size(), len2 = nums2.size();
            std::vector<std::vector<int>> dp(len1+1, std::vector<int>(len2+1, -1e7));
            for(int i=1; i<=len1; ++i){
                for(int j=1; j<=len2; ++j){
                    dp[i][j] = nums1[i-1] * nums2[j-1];
                    dp[i][j] = std::max(dp[i][j], dp[i-1][j-1]);
                    dp[i][j] = std::max(dp[i][j], dp[i-1][j-1]+nums1[i-1]*nums2[j-1]);
                    dp[i][j] = std::max(dp[i][j], dp[i-1][j]);
                    dp[i][j] = std::max(dp[i][j], dp[i][j-1]);
                }
            }
            return dp[len1][len2];
        }
};

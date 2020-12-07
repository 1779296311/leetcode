/*********************************************
*     ------------------------
*     ------------------------
*     file name: WEEK.cpp
*     author   : @ JY
*     date     : 2020--09--20
**********************************************/
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <string>
#include <algorithm>
#include <stack>
#include <map>
#include <cmath>
#include <climits>
#include <vector>
#include <queue>
#include <cstring>
#include <numeric>
#include <set>
#include <bitset>
#include <stdlib.h>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
namespace WK128{
    class Solution{
        public:
            int miniminIncompatibility_dp_0(std::vector<int> &nums, int k){
                const int INF = 0x3f3f3f3f;
                std::sort(begin(nums), end(nums));
                int len = nums.size(), f = 0, no = 1;
                std::vector<int> dp(1 << len, INF);
                std::vector<std::pair<int, int>> value;
                for(int mask=0; mask<(1 << len); ++mask){
                    if(__builtin_popcount(mask) != (len / k))continue;
                    f = 0, no = 0;
                    for(int i=0; i<len; ++i){
                        if(!(mask & (1 << i)))continue;
                        if((no = f & (1 << nums[i])))break;
                        f |= 1 << nums[i];
                    }
                    if(no)continue;
                    int max_ = INT_MIN, min_ = INT_MAX;
                    for(int i=0; i<len; ++i){
                        if(!((1<<i) & mask))continue;
                        max_ = std::max(max_, nums[i]);
                        min_ = std::min(min_, nums[i]);
                    }
                    value.emplace_back(mask, max_ - min_);
                }
                dp[0] = 0;
                for(int mask=0; mask<(1 << len); ++mask){
                    if(__builtin_popcount(mask) % (len / k))continue;
                    for(auto &[nxt, v] : value){
                        if(nxt & mask)continue;
                        dp[mask | nxt] = std::min(dp[mask | nxt], dp[mask] + v);
                    }
                }
                return dp[(1 << len) - 1] == INF ? -1 : dp[(1 << len) - 1];

            }
            int miniminIncompatibility_dp_1(std::vector<int> &nums, int k){
                const int INF = 0x3f3f3f3f;
                std::sort(begin(nums), end(nums));
                int len = nums.size(), f = 0, no = 1;
                std::vector<int> value(1 << len, INF), dp(1 << len, INF);
                for(int mask=0; mask<(1 << len); ++mask){
                    if(__builtin_popcount(mask) != (len / k))continue;
                    f = 0, no = 0;
                    for(int i=0; i<len; ++i){
                        if(!(mask & (1 << i)))continue;
                        if((no = f & (1 << nums[i])))break;
                        f |= 1 << nums[i];
                    }
                    if(no)continue;
                    int max_ = INT_MIN, min_ = INT_MAX;
                    for(int i=0; i<len; ++i){
                        if(!((1<<i) & mask))continue;
                        max_ = std::max(max_, nums[i]);
                        min_ = std::min(min_, nums[i]);
                    }
                    value[mask] = max_ - min_;
                }
                dp[0] = 0;
                for(int mask=0; mask<(1 << len); ++mask){
                    if(__builtin_popcount(mask) % (len / k))continue;
                    for(int pre = mask; pre; pre = mask & (pre-1)){
                        if(value[pre] == INF || dp[mask ^ pre] == INF)continue;
                        dp[mask] = std::min(dp[mask], dp[mask^pre] + value[pre]);
                    }
                }
                return dp[(1 << len) - 1] == INF ? -1 : dp[(1 << len) - 1];
            }
            int miniminIncompatibility_fuck(std::vector<int> &nums, int k){
                int n = nums.size() / k, ans = INT_MAX, len = nums.size(), type = 0;
                if(n == 1)return 0;
                std::sort(begin(nums), end(nums));
                std::vector<int> bits(k), vi(len),
                                 mp(len+1), mp1(len+1), mp2(len+1), mp3(len+1);
                for(auto &x : nums)type += (1 == ++mp3[x]);
                std::function<int(void)> _calc = [&](void){
                    int ans = 0;
                    for(auto &x : bits){
                        int l = 31 - __builtin_clz(x);
                        int r = __builtin_ctz(x);
                        ans += nums[l] - nums[r];
                    }
                    return ans;
                };
                std::function<void(int, int, int)> _dfs = [&](int t, int z, int b){
                    if(type + (z==n) < k - t)return;
                    if(t == k){
                        ans = std::min(ans, _calc());
                        return;
                    }
                    if(z == n){
                        bits[t] = b;
                        std::vector<int> mp1 = mp;
                        mp  = mp2;
                        _dfs(t+1, 0, 0);
                        mp  = mp1;
                        return ;
                    }
                    for(int i=0; i<len; ++i){
                        if(vi[i] || mp[nums[i]])continue;
                        vi[i] = 1;
                        mp[nums[i]] = 1;
                        type -= (!--mp3[nums[i]]);
                        _dfs(t, z+1, b | (1 << i));
                        mp[nums[i]] = 0;
                        type += (!mp3[nums[i]]++);
                        vi[i] = 0;
                    }
                    return;
                };
                _dfs(0, 0, 0);
                return ans == INT_MAX ? -1 : ans;
            }
            int concatentedBinary(int n){
                const int MOD = 1e9 + 7;
                long long ans = 0, shift = 0;
                for(int i=1; i<=n; ++i){
                    shift += !(i & (i-1));
                    ans = ((ans << shift) + i) % MOD;
                }
                return ans;
            }
            int maxOperations(std::vector<int>& nums, int k){
                int ans = 0;
                std::unordered_map<int, int> mp;
                for(auto &x : nums)++mp[x];
                for(auto &c : nums){
                    int t = std::min(mp[c], mp[k - c]);
                    if(c == k - c)t /= 2;
                    if(t <= 0)continue;
                    ans += t;
                    mp[c] -= t, mp[k - c] -= t;
                }
                return ans;
            }

            std::string interpret(std::string command){
                std::string ans;
                int len = command.size();
                for(int i=0; i<len; ++i){
                    if(command[i] == 'G'){
                        ans += 'G';
                    }else{
                        if(command[i + 1] == ')'){
                            ans += 'o';
                        }else{
                            ans += 'a';
                            ans += 'l';
                            ++i;
                            ++i;
                        }
                        ++i;
                    }
                }
                return ans;
            }
    };
};
namespace WK217{
    struct SMALLESTRANGE{
        static std::pair<int, int> smallestRange1
            (std::vector<std::vector<int>> &nums){
                int len = nums.size(), resl = INT_MAX, resr = INT_MIN, l = 0, r = 0, maxr;
                std::unordered_map<int, std::vector<int>> mp;
                std::vector<int> hset(len);
                for(int i=0; i<len; ++i){
                    for(auto &p : nums[i]){
                        mp[p].emplace_back(i);
                        resl = std::min(resl, p);
                        resr = std::min(resr, p);
                    }
                }
                l = resl, r = resl - 1, maxr = resr;
                while(r < maxr){
                    if(mp.count(++r)){
                        for(auto i : mp[r]){
                            if(++hset[i] == 1)--len;
                        }
                        while(!len){
                            if(resr - resl < r - l)resr = r, resl = l;
                            if(mp.count(l)){
                                for(auto i : mp[l]){
                                    if(!--hset[i])++len;
                                }
                            }
                            while(l < r && !mp.count(l));
                        }
                    }
                }
                return {resl, resr};
            }
        static std::pair<int, int> smallestRange
            (std::vector<std::vector<int>> &nums){
                int len = nums.size(), resl = 0, resr = INT_MAX, l = 0, r = 0;
                std::vector<int> next(len);
                std::function<bool(const int &a, const int &b)> _cmp
                    = [&](const int &a, const int &b){
                        return nums[a][next[a]] > nums[b][next[b]];
                    };
                std::priority_queue<int, std::vector<int>, decltype(_cmp)> q(_cmp);
                for(int i=0; i<len; ++i){
                    q.push(i);
                    r = std::max(r, nums[i][0]);
                }
                while(1){
                    int cur = q.top();q.pop();
                    l = nums[cur][next[cur]];
                    if(resr - resl > r - l){
                        resr = r, resl = l;
                    }
                    if(++next[cur] == nums[cur].size())break;
                    r = std::max(r, nums[cur][next[cur]]);
                    q.push(cur);
                }
                return {resl, resr};
        }
    };
    int minimumDeviation(std::vector<int> &nums){
        int len = nums.size();
        std::vector<std::vector<int>> t(len);
        for(int i=0; i<len; ++i){
            t[i].emplace_back(nums[i]);
            if(nums[i] & 1){
                t[i].emplace_back(nums[i] << 1);
            }else{
                while(!(nums[i] & 1)) t[i].emplace_back(nums[i] >>= 1);
                t[i].emplace_back(nums[i]);
                std::reverse(begin(t[i]), end(t[i]));
            }
        }
        auto [l, r] = SMALLESTRANGE::smallestRange(t);
        return r - l;
    }
    int minMoves(std::vector<int> &nums, int limit){
        int len = nums.size(), ans = len, sum = len;
        std::vector<int> dif(limit * 2 + 2);
        for(int i=0; i<len/2; ++i){
            --dif[1+std::min(nums[i], nums[len-i-1])];
            ++dif[limit + std::max(nums[i], nums[len-i-1]) + 1];
            --dif[nums[i]+nums[len-i-1]];
            ++dif[nums[i]+nums[len-i-1] + 1];
        }
        for(int i=2; i<=limit*2; ++i)ans = std::min(ans, sum += dif[i]);
        return ans;
    }
    std::vector<int> mostCompetitive(std::vector<int> &nums, int k){
        int len = nums.size();
        std::vector<int> ans;
        for(int i=0; i<len; ++i){
            while(ans.size() && ans.back() > nums[i]
                    && (ans.size() + len - i) > k){
                ans.pop_back();
            }
            if(ans.size() != k)ans.push_back(nums[i]);
        }
        return ans;
    }
    int maximimWealth(std::vector<std::vector<int>> &accounts){
        int ans = 0;
        for(auto &m : accounts){
            ans = std::max(ans, std::accumulate(begin(m), end(m), 0));
        }
        return ans;
    }
};
namespace WK216{
    class Solution{
        public:
            int minimumEffort(std::vector<std::vector<int>> &tasks){
                std::sort(begin(tasks), end(tasks), [&](auto &a, auto &b){
                        int d1 = a[1] - a[0], d2 = b[1] - b[0];
                        return d1==d2 ? a[1] > b[1] : d1 > d2; });
                std::function<bool(int)> _calc = [&](int m){
                    for(auto &x : tasks){
                        if(m < x[1])return false;
                        m -= x[0];
                    }
                    return true;
                };
                int l = 1, r = 1e9;
                while(l < r){
                    int m = l + ((r - l) >> 1);
                    if(_calc(m)){
                        r = m;
                    }else{
                        l = m + 1;
                    }
                }
                return r;
            }
            int waysToMakeFair(std::vector<int> &nums){
                nums.insert(begin(nums), 2, 0);
                nums.push_back(0); nums.push_back(0);
                int len = nums.size(), res = 0, sumo = 0, sume = 0;
                std::vector<int> eve(len), odd(len);
                odd[0] = nums[0], eve[1] = nums[1];
                for(int i=2; i<len; i+=2)sumo = std::max(sumo, odd[i] = odd[i-2] + nums[i]);
                for(int i=3; i<len; i+=2)sume = std::max(sume, eve[i] = eve[i-2] + nums[i]);
                for(int i=2; i<len-2; ++i){
                    if(i & 1){
                        res += (eve[i-2] + sumo - odd[i-1])
                                            ==
                               (odd[i-1] + sume - eve[i]);
                    }else{
                        res += (eve[i-1] + sumo - odd[i])
                                            ==
                               (odd[i-2] + sume - eve[i-1]);
                    }
                }
                return res;
            }
            std::string getSmallestString(int n, int k){
                std::string res;
                while(n){
                    char c = std::min(k - n-- + 1, 26) + 'a';
                    res += c;
                    k -=  c - 'a' + 1;
                }
                std::reverse(begin(res), end(res));
                return res;
            }
            bool arayStringAreEqual(std::vector<std::string> &word1,
                                    std::vector<std::string> &word2){
                int s1 = word1.size(), s2 = word2.size();
                int i = 0, j = 0, i1 = 0, j1 = 0;
                while(i<s1 && j<s2){
                    if(word1[i][i1++] != word2[j][j1++])return false;
                    if(i1 == word1[i].size())++i, i1 = 0;
                    if(j1 == word2[j].size())++j, j1 = 0;
                }
                return i==s1 && j==s2;
            }
    };
};
namespace WE215{
//5601. 设计有序流
    class OrderedStream{
        public:
            int n, pre;
            std::map<int, std::string> mp;
            OrderedStream (int n) : n(n), pre(1){}
            std::vector<std::string> insert(int id, std::string value){
                std::vector<std::string> res;
                mp.emplace(id, value);
                if(mp.count(pre)){
                    auto it = mp.lower_bound(pre);
                    int p = id - 1;
                    for(; it!=end(mp); ++it){
                        auto [n, s] = *it;
                        if(n - p != 1)break;
                        p = n;
                        res.emplace_back(s);
                    }
                    pre = p + 1;
                }
                return res;
            }
    };

    class Solution{
        public:
//5604. 最大化网格幸福感
            int getMaxGridHappiness_dp_0(int m, int n, int intr, int ext){
                int mask_span[729][6];
                int dp[729][25][7][7];
                int truncate[729][3];
                int all = std::pow(3, n), mod = all / 3;
                std::function<int(int, int)> _calc = [&](int in, int ex){
                    if(!in || !ex)return 0;
                    if(in==1 && ex==1)return -60;
                    if(in==2 && ex==2)return 40;
                    return -10;
                };
                for(int state=0; state<all; ++state){
                    for(int t=state, i=0; i<n; ++i){
                        mask_span[state][n - i - 1] = t % 3;
                        t /= 3;
                    }
                    truncate[state][0] = (state % mod) * 3 + 0;
                    truncate[state][1] = (state % mod) * 3 + 1;
                    truncate[state][2] = (state % mod) * 3 + 2;
                }
                std::memset(dp, -1, sizeof dp);
                std::function<int(int, int, int, int)> _dfs
                    = [&](int pre, int pos, int in, int ex){
                        if((pos == n*m) || (!in && !ex))return 0;
                        if(dp[pre][pos][in][ex] != -1)return dp[pre][pos][in][ex];
                        int ans = _dfs(truncate[pre][0], pos+1, in, ex);
                        if(in){
                            ans = std::max(ans,
                                    120 + _calc(1, mask_span[pre][0]) +
                                    ((pos % n) ? _calc(1, mask_span[pre][n-1]) : 0) +
                                    _dfs(truncate[pre][1], pos+1, in-1, ex));
                        }
                        if(ex){
                            ans = std::max(ans,
                                    40 + _calc(2, mask_span[pre][0]) +
                                    ((pos % n) ? _calc(2, mask_span[pre][n-1]) : 0) +
                                    _dfs(truncate[pre][2], pos + 1, in, ex - 1));
                        }
                        return dp[pre][pos][in][ex] = ans;
                    };
                return _dfs(0, 0, intr, ext);
            }
            int getMaxGridHappiness_dp_1(int m, int n, int intr, int ext){
                int mask_span[729][6];
                int dp[729][6][7][7];
                int in_cnt[729], ex_cnt[729], inner_score[729], outer_score[729][729];
                std::function<int(int, int)> _calc = [&](int in, int en){
                    if(in==1 && en==1)return -60;
                    if(in==2 && en==2)return 40;
                    return -10;
                };
                int all = std::pow(3, n), res = 0;
                for(int state=0; state<all; ++state){
                    for(int t=state,i=0; i<n; ++i){
                        mask_span[state][i] = t % 3;
                        t /= 3;
                    }
                    in_cnt[state] = ex_cnt[state] = inner_score[state] = 0;
                    for(int i=0; i<n; ++i){
                        if(!mask_span[state][i])continue;
                        if(mask_span[state][i] == 1){
                            ++in_cnt[state];
                            inner_score[state] += 120;
                        }else{
                            ++ex_cnt[state];
                            inner_score[state] += 40;
                        }
                        if(!i || !mask_span[state][i-1])continue;
                        inner_score[state] += _calc(mask_span[state][i], mask_span[state][i-1]);
                    }
                }
                for(int pre=0; pre<all; ++pre){
                    for(int cur=0; cur<all; ++cur){
                        outer_score[pre][cur] = 0;
                        for(int i=0; i<n; ++i){
                            if(!mask_span[pre][i] ||
                               !mask_span[cur][i]) continue;
                            outer_score[pre][cur] += _calc(mask_span[pre][i], mask_span[cur][i]);
                        }
                    }
                }
                std::memset(dp, -1, sizeof(dp));
                std::function<int(int, int, int, int)> _dfs
                    = [&](int pre, int i, int in, int ex){
                        if((!in && !ex) || (i == m))return 0;
                        if(dp[pre][i][in][ex] != -1)return dp[pre][i][in][ex];
                        int ans = 0;
                        for(int cur=0; cur<all; ++cur){
                            if(in_cnt[cur] > in || ex_cnt[cur] > ex)continue;
                            int score = inner_score[cur] + outer_score[pre][cur];
                            ans = std::max(ans,
                                          _dfs(cur, i + 1, in - in_cnt[cur], ex - ex_cnt[cur]) + score);
                        }
                        return dp[pre][i][in][ex] = ans;
                    };
                return _dfs(0, 0, intr, ext);
            }
            int getMaxGridHappiness_fuck(int m, int n, int intr, int ext){
                std::vector<int> _fun {0, 1, 0, -1, 0};
                std::vector<std::vector<int>> grid(m, std::vector<int>(n));
                int res = 0;
                std::function<int(void)> _calc = [&](void){
                    int ans = 0;
                    for(int i=0; i<m; ++i){
                        for(int j=0; j<n; ++j){
                            if(!grid[i][j] || grid[i][j] == 3)continue;
                            int k = 0;
                            for(int f=0; f<4; ++f){
                                int i1 = i + _fun[f];
                                int j1 = j + _fun[f + 1];
                                if(i1 < 0 || j1<0 || i1>=m || j1>=n ||
                                   !grid[i1][j1] || grid[i1][j1] == 3){
                                    continue;
                                }
                                ++k;
                            }
                            ans += grid[i][j]==2 ? (40 + k * 20) : (120 - k * 30);
                        }
                    }
                    return ans;
                    //for(int i=0; i<m; ++i){
                        //for(int j=0; j<n; ++j){
                            //std::cout<<grid[i][j]<<"  ";
                        //}
                        //std::cout<<std::endl;
                    //}
                    //std::cout<<"---------------------\n";
                };
                int dp[6][6][7][7][4];
                bzero(dp, 2000);
                std::function<void(int, int, int, int)> _dfs
                    = [&](int i, int j, int in, int ex){
                        res = std::max(res, _calc());
                        //if(dp[i][j][in][ex][grid[i][j]])return;
                        if((i==m && j==n) || (!in && !ex)){
                            return;
                        }
                        //dp[i][j][in][ex][grid[i][j]] = 1;
                        for(int f=0; f<4; ++f){
                            int i1 = i + _fun[f];
                            int j1 = j + _fun[f + 1];
                            if(i1<0 || j1<0 || i1>=m || j1>=n || grid[i1][j1] != 0){
                                continue;
                            }
                            grid[i1][j1] = 3;
                            _dfs(i1, j1, in, ex);
                            grid[i1][j1] = 0;
                            if(in){
                                grid[i1][j1] = 1;
                                _dfs(i1, j1, in-1, ex);
                                grid[i1][j1] = 0;
                            }
                            if(ex){
                                grid[i1][j1] = 2;
                                _dfs(i1, j1, in, ex-1);
                                grid[i1][j1] = 0;
                            }
                        }
                };
                if(intr){
                    grid[0][0] = 1;
                    _dfs(0, 0, intr-1, ext);
                    grid[0][0] = 0;
                }
                if(ext){
                    grid[0][0] = 2;
                    _dfs(0, 0, intr, ext-1);
                    grid[0][0] = 0;
                }
                //for(int i=0; i<m; ++i){
                    //for(int j=0; j<n; ++j){
                        //if(intr){
                            //grid[i][j] = 1;
                            //_dfs(i, j, intr-1, ext);
                            //grid[i][j] = 0;
                        //}
                        //if(ext){
                            //grid[i][j] = 2;
                            //_dfs(i, j, intr, ext-1);
                            //grid[i][j] = 0;
                        //}
                    //}
                //}
                return res;
            }
//5602. 将 x 减到 0 的最小操作数
            int minOperations(std::vector<int> &nums, int x){
                int l = 0, r = 0, cur = 0, res = -1, len = nums.size();
                int sum = std::accumulate(begin(nums), end(nums), 0);
                while(r < len){
                    cur += nums[r];
                    while(l<=r && cur > sum-x)cur -= nums[l++];
                    if(cur == sum-x)res = std::max(res, r - l + 1);
                    ++r;
                }
                return res==-1 ? -1 : len - res;
            }
//5603. 确定两个字符串是否接近
            bool closeStrings(std::string word1, std::string word2){
                if(word1.size() != word2.size())return false;
                std::vector<int> mp1(26), mp2(26);
                int len = word1.size();
                for(int i=0; i<len; ++i){
                    ++mp1[word1[i] - 'a'];
                    ++mp2[word2[i] - 'a'];
                }
                for(int i=0; i<26; ++i){
                    if(!mp1[i] ^ !mp2[i])return false;
                }
                std::sort(begin(mp1), end(mp1));
                std::sort(begin(mp2), end(mp2));
                return mp1 == mp2;
            }
    };
};
namespace WK214{
    class Solution{
        public:
//5564. 通过指令创建有序数组
            int createSortedArray_better(std::vector<int> &instructions){
                using ll = long long;
                int max_ = *std::max_element(begin(instructions), end(instructions));
                int MOD = 1e9 + 7;
                std::vector<int> tree(max_+1);
                std::function<int(int)> _lowbit = [&](int x){
                    return x & - x; };
                std::function<void(ll, ll)> _update = [&](ll x, ll v){
                    for(;x<=max_; x+=_lowbit(x))tree[x] += v; };
                std::function<ll(ll)> _query = [&](ll x){
                    ll res = 0;
                    for(; x ; x-=_lowbit(x))res = (res + tree[x]) % MOD;
                    return res;
                };
                ll res = 0, len = instructions.size();
                for(int i=0; i<len; ++i){
                    int x = instructions[i];
                    res  += std::min(_query(x-1), i-_query(x));
                    res  %= MOD;
                    _update(x, 1);
                }
                return res % MOD;
            }
            int createSortedArray(std::vector<int> &instructions){
                using ll = long long;
                int n    = instructions.size();
                ll res   = 0;
                int MOD  = 1e9 + 7;
                std::vector<int> tr1(100010), tr2(100010);
                std::function<int(int x)> _lowbit = [&](int x){
                    return x & -x; };
                std::function<void(int, int)> _add = [&](int x, int c){
                    for(; x; x-=_lowbit(x))tr1[x] = (c + tr1[x]) % MOD; };
                std::function<int(int x)> _sum = [&](int x){
                    int res = 0;
                    for(; x<=n; x+=_lowbit(x))res = (tr1[x] + res) % MOD;
                    return res;
                };
                for(int i=0; i<n; ++i){
                    int k = instructions[i];
                    res += std::max(std::min(_sum(k)-tr2[k], i - _sum(k)), 0);
                    res %= MOD;
                    _add(k, 1);
                    ++tr2[k];
                }
                return res % MOD;
            }
//5563. 销售价值减少的颜色球
            int maxProfit(std::vector<int> &inventory, int orders){
                using ll = long long;
                int l = 0, r = *max_element(begin(inventory), end(inventory));
                int MOD = 1e9 + 7, T = -1;
                while(l <= r){
                    int mid = l + ((r - l) >> 1);
                    ll total = std::accumulate(begin(inventory), end(inventory), 0LL, [&](ll acc, int ai){
                            return acc + std::max(ai - mid, 0); });
                    if(total <= orders){
                        T = mid;
                        r = mid - 1;
                    }else{
                        l = mid + 1;
                    }
                }
                int rest = orders - std::accumulate(begin(inventory), end(inventory), 0, [&](int acc, int ai){
                        return acc + std::max(ai - T, 0); });
                std::function<ll(ll a, ll b)> _sum = [&](ll a, ll b){
                    return static_cast<ll>(a+b) * (b-a+1)/2;
                };
                ll res = 0;
                for(auto ai : inventory){
                    if(ai > T){
                        res += ((ai + T + 1) * (ai - T)) >> 1;
                        res %= MOD;
                        orders -= ai - T;
                    }
                }
                res += (ll)T * (ll)orders;
                //for(int ai : inventory){
                    //if(ai >= T){
                        //if(rest > 0){
                            //res += _sum(T, ai);
                            //--rest;
                        //}else{
                            //res += _sum(T+1, ai);
                        //}
                    //}
                //}
                return res % MOD;
            }
            int maxProfit_fuck(std::vector<int> &inventory, int orders){
                using ll = long long;
                ll MOD = 1e9 + 7, res = 0;
                std::priority_queue<ll> q(begin(inventory), end(inventory));
                for(int i=0; i<orders; ++i){
                    ll v = q.top();
                    res  = (res + v) % MOD;
                    q.pop();
                    q.push(v-1);
                }
                return res;
            }
//5562. 字符频次唯一的最小删除次数
            int minDeleteions_hs(std::string s){
                std::vector<int> mp(26);
                for(auto &c : s)++mp[c-'a'];
                std::unordered_set<int> fre;
                int res = 0;
                for(auto x : mp){
                    while(x && fre.count(x))--x, ++res;
                    if(x)fre.insert(x);
                }
                return res;
            }
            int minDeleteions(std::string s){
                std::vector<int> mp(26);
                for(auto &c : s)++mp[c-'a'];
                std::sort(begin(mp), end(mp), std::greater<int>());
                int res = 0, pre = mp[0];
                for(int i=1; i<26 && mp[i]; ++i){
                    if(pre > mp[i]){
                        pre = mp[i];
                    }else{
                        pre = std::max(pre-1, 0);
                        res += mp[i] - pre;
                    }
                }
                return res;
            }
//5561. 获取生成数组中的最大值
            int getMaximumGenerated(int n){
                if(!n)return n;
                std::vector<int> ans(n+1);
                ans[1] = 1;
                int res = 0;
                for(int i=2; i<=n; ++i){
                    if(i & 1){
                        ans[i] = ans[i/2] + ans[i/2+1];
                    }else{
                        ans[i] = ans[i/2];
                    }
                    res = std::max(res, ans[i]);
                }
                return res;
            }
    };
};
namespace WK213{
    class Solution{
        public:
//5600. 第 K 条最小指令
            std::string kthSmallestPath(std::vector<int> &destination, int k){
                int m = destination[0], n = destination[1];
                std::vector<std::vector<int>> comb(n+m, std::vector<int>(n+m));
                comb[0][0] = 1;
                for(int i=1; i<n+m; ++i){
                    comb[i][0] = 1;
                    for(int j=1; j<=i; ++j){
                        comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
                    }
                }
                std::string res;
                for(int i=0, len=n+m; i<len; ++i){
                    if(n > 0){
                        int o = comb[m+n-1][n-1];
                        if(k > o){
                            res += 'V';
                            --m;
                            k -= o;
                        }else{
                            res += 'H';
                            --n;
                        }
                    }else{
                        res += 'V';
                    }
                }
                return res;
            }
            std::string kthSmallestPath_fuck(std::vector<int> &destination, int k){
                int m = destination[0], n = destination[1];
                std::vector<std::vector<std::set<std::string>>>
                    dp(m+1, std::vector<std::set<std::string>>(n+1));
                std::string temp = "";
                for(int i=1; i<=m; ++i)dp[i][0].insert(temp+="V");
                temp = "";
                for(int i=1; i<=n; ++i)dp[0][i].insert(temp+="H");
                for(int i=1; i<=m; ++i){
                    for(int j=1; j<=n; ++j){
                        for(auto &&w : dp[i-1][j]){
                            dp[i][j].insert(w + 'V');
                        }
                        for(auto &&w : dp[i][j-1]){
                            dp[i][j].insert(w + 'H');
                        }
                    }
                }
                std::string res;
                for(auto &s : dp[m][n]){
                    res = s;
                    if(!k--)break;
                }
                return res;
            }
//5556. 可以到达的最远建筑
            int furthestBuilding(std::vector<int> &heights, int bricks, int ladders){
                std::priority_queue<int, std::vector<int>, std::greater<int>> q;
                int len = heights.size();
                for(int i=1; i<len; ++i){
                    int dif = heights[i] - heights[i-1];
                    if(dif > 0){
                        q.push(dif);
                        if(q.size() > ladders){
                            if((bricks -= q.top()) < 0)return i-1;
                            q.pop();
                        }
                    }
                }
                return len - 1;
            }
//5555. 统计字典序元音字符串的数目
            int countVomelString(int n){
                int a = 1, e = 1, i = 1, o = 1, u = 1;
                for(int k=1; k<n; ++k){
                    u = a + e + i + o + u;
                    o = a + e + i + o;
                    i = a + e + i;
                    e = a + e;
                    a = a;
                }
                return a + e + i + o + u;
            }
//5554. 能否连接形成数组
            bool canFormArray(std::vector<int> &arr,
                    std::vector<std::vector<int>> &pieces){
                int len = arr.size(), all = 0, i = 0, j = 0, k = 0;
                int size = pieces.size();
                while(i < len){
                    for(j=0; j<size && pieces[j][0]!=arr[i]; ++j);
                    if(j == size)return false;
                    for(k=0; i<len && k<pieces[j].size() && pieces[j][k]==arr[i]; ++i,++k,++all);
                    if(k != pieces[j].size())return false;
                }
                return all == len;
            }
    };

};
namespace WK212{
    class Solution{
        public:
//5156. 矩阵转换后的秩
            std::vector<std::vector<int>> matrixRankTeansform1(std::vector<std::vector<int>> &matrix){
                int m = matrix.size(), n = matrix[0].size();
                std::vector<int> _p(m * n * 2), rowmax_(m), colmax_(n);
                std::vector<std::vector<int>> res(m, std::vector<int>(n));
                std::iota(begin(_p), end(_p), 0);
                std::function<int(int)> _find = [&](int i){
                    return _p[i] == i ? i : _p[i] = _find(_p[i]); };
                std::function<void(int, int)> _union = [&](int a, int b){
                    _p[_find(a)] = _p[_find(b)]; };
                std::map<int, std::vector<int>> mp, temp;
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j)mp[matrix[i][j]].push_back(i * n + j);
                }
                int len = mp.size(), i = 0;
                std::vector<int> vals(len);
                for(auto &[v, vs] : mp)vals[i++] = v;
                for(auto v : vals){
                    for(int id : mp[v]){
                        int x = id / n, y = id % n;
                        _union(_find(x), _find(y+m));
                    }
                    temp.clear();
                    for(int id : mp[v]){
                        int x = id / n, y = id % n;
                        temp[_find(x)].push_back(id);
                    }
                    for(auto &[k, r] : temp){
                        int rank_ = 0;
                        for(auto id : r){
                            int x = id / n, y = id % n;
                            rank_ = std::max({rank_, rowmax_[x], colmax_[y]});
                        }
                        ++rank_;
                        for(auto id : r){
                            int x = id / n, y = id % n;
                            rowmax_[x] = colmax_[y] = res[x][y] = rank_;
                            _p[x] = x;
                            _p[y+m] = y+m;
                        }
                    }
                }
                return res;
            }
            std::vector<std::vector<int>> matrixRankTeansform(std::vector<std::vector<int>> &matrix){
                int m = matrix.size(), n = matrix[0].size();
                std::vector<int> _p(m * n);
                std::iota(begin(_p), end(_p), 0);
                std::function<int(int)> _find = [&](int i){
                    return _p[i] == i ? i : _p[i] = _find(_p[i]); };
                std::function<void(int, int)> _union = [&](int a, int b){
                    _p[_find(a)] = _p[_find(b)]; };
                std::vector<std::vector<int>> res(m, std::vector<int>(n));
                std::vector<int> rowmax_(m), colmax_(n);
                std::unordered_map<int, std::vector<int>> mp;
                for(int i=0; i<m; ++i){
                    mp = {};
                    for(int j=0; j<n; ++j){
                        mp[matrix[i][j]].push_back(i * n + j);
                    }
                    for(auto &[val, vs] : mp){
                        int size = vs.size();
                        for(int k=1; k<size; ++k)_union(vs[k-1], vs[k]);
                    }
                }
                for(int j=0; j<n; ++j){
                    mp = {};
                    for(int i=0; i<m; ++i){
                        mp[matrix[i][j]].push_back(i * n + j);
                    }
                    for(auto &[val, vs] : mp){
                        int size = vs.size();
                        for(int k=1; k<size; ++k)_union(vs[k-1], vs[k]);
                    }
                }
                struct _node{
                    int id, pa, val;
                    _node(int id, int pa, int val) : id(id), pa(pa), val(val) {}
                    bool operator < (const _node &other) const {
                        return val == other.val ? pa < other.pa : val < other.val; }
                };
                std::vector<_node> nodes;
                for(int i=0; i<m; ++i){
                    for(int j=0; j<n; ++j){
                        nodes.emplace_back(i*n+j, _find(i*n+j), matrix[i][j]);
                    }
                }
                std::sort(begin(nodes), end(nodes));
                int rank_ = 0, len = nodes.size(), j, p;
                for(int i=0; i<len; i=j){
                    j = i, p = nodes[i].pa, rank_ = 0;
                    while(j<len && p == nodes[j].pa)++j;
                    for(int k=i; k<j; ++k){
                        int x = nodes[k].id / n;
                        int y = nodes[k].id % n;
                        rank_ = std::max({rank_, rowmax_[x], colmax_[y]});
                    }
                    ++rank_;
                    for(int k=i; k<j; ++k){
                        int x = nodes[k].id / n;
                        int y = nodes[k].id % n;
                        rowmax_[x] = colmax_[y] = res[x][y] = rank_;
                    }
                }
                return res;
            }
//5548. 最小体力消耗路径
            int minimumEffortPath_uf(std::vector<std::vector<int>> &heights){
                int m = heights.size(), n = heights[0].size();
                std::vector<int> _p(n*m + 1);
                std::iota(begin(_p), end(_p), 0);
                std::function<int(int)> _find = [&](int i){
                    return _p[i] == i ? i : _p[i] = _find(_p[i]); };
                std::function<void(int, int)> _union = [&](int a, int b){
                    return _p[_find(a)] = _p[_find(b)]; };
                struct _node{
                    int id1, id2, d;
                    _node(int i1, int i2, int d) : id1(i1), id2(i2), d(d) {}
                    bool operator < (const _node &other) const {
                        return d < other.d; }
                };
                std::vector<_node> e;
                for(int i=0; i<m; ++i){
                    for(int j =0; j<n; ++j){
                        int id = i * n + j;
                        if(i)e.emplace_back(id, id - n, abs(heights[i][j] - heights[i-1][j]));
                        if(j)e.emplace_back(id, id - 1, abs(heights[i][j] - heights[i][j-1]));
                    }
                }
                std::sort(begin(e), end(e));
                for(auto &ed : e){
                    _union(ed.id1, ed.id2);
                    if(_find(0) == _find(m*n-1))return ed.d;
                }
                return 0;
            }
            int minimumEffortPath_dij(std::vector<std::vector<int>> &heights){
                struct _node{
                    int x, y, d;
                    _node (int x, int y, int d) : x(x), y(y), d(d) {};
                    bool operator < (const _node &other) const {
                        return d > other.d; }
                };
                int m = heights.size(), n = heights[0].size(), INF = 0x3f3f3f3f;
                std::vector<int> vi(n*m + n), dis(n*m + n, INF), _fun {0, 1, 0, -1, 0};
                std::priority_queue<_node> q;
                q.push({0, 0, 0}), dis[0] = 0;
                while(q.size()){
                    auto [i, j, d] = q.top(); q.pop();
                    if(vi[i*n + j])continue;
                    vi[i*n + j] = 1;
                    for(int f=0; f<4; ++f){
                        int i1 = _fun[f] + i;
                        int j1 = _fun[f + 1] + j;
                        if(i1<0 || j1<0 || i1>=m || j1>=n)continue;
                        if(vi[i1*n+j1])continue;
                        int d1 = abs(heights[i][j] - heights[i1][j1]);
                        dis[i1*n + j1] = std::min(dis[i1*n + j1], std::max(d1, d));
                        q.push({i1, j1, std::max(d1, d)});
                    }
                }
                return dis[n*m - 1];
            }
            int minimumEffortPath(std::vector<std::vector<int>> &heights){
                int m = heights.size(), n = heights[0].size();
                if(m==1){
                    int ans = 0;
                    for(int i=1; i<n; ++i)ans = std::max(ans, heights[0][i] - heights[0][i-1]);
                    return ans;
                }
                if(n==1){
                    int ans = 0;
                    for(int i=1; i<m; ++i)ans = std::max(ans, heights[i][0] - heights[i-1][0]);
                    return ans;
                }
                int l = 0, r = 0;
                for(int i=0; i<m-1; ++i){
                    for(int j=0; j<n-1; ++j){
                        r = std::max(r, abs(heights[i][j] - heights[i+1][j]));
                        r = std::max(r, abs(heights[i][j] - heights[i][j+1]));
                    }
                }
                std::vector<int> vi(n*m+n+n), fun = {1, 0, -1, 0, 1};
                std::function<bool(int, int, int)> _dfs = [&](int mid, int i, int j){
                    if(i==m-1 && j==n-1)return true;
                    vi[i * n + j] = 1;
                    for(int f=0; f<4; ++f){
                        int i1 = fun[f] + i;
                        int j1 = fun[f+1] + j;
                        if(i1>=m || j1>=n || i1<0 || j1<0)continue;
                        if(vi[i1*n + j1] || abs(heights[i][j]-heights[i1][j1])>mid)continue;
                        if(_dfs(mid, i1, j1))return true;
                    }
                    return false;
                };
                while(l < r){
                    int m = l + ((r - l) >> 1);
                    std::fill(begin(vi), end(vi), 0);
                    if(_dfs(m, 0, 0)){
                        r = m;
                    }else{
                        l = m + 1;
                    }
                }
                return r;
            }
//5547. 等差子数组
            std::vector<bool> checkAirthmetichSubarrays(std::vector<int> &nums,
                    std::vector<int> &l, std::vector<int> &r){
                int len1 = nums.size(), len2 = l.size();
                std::vector<bool> res(len2);
                std::function<bool(int, int)> _check = [&](int ll, int rr){
                    std::vector<int> temp(begin(nums)+ll, begin(nums)+rr+1);
                    std::sort(begin(temp), end(temp));
                    int d = temp[1] - temp[0];
                    for(int i=2; i<rr-ll+1; ++i){
                        if(temp[i] - temp[i-1] != d)return false;
                    }
                    return true;
                };
                for(int i=0; i<len2; ++i){
                    res[i] = l[i] < r[i]  && _check(l[i], r[i]);
                }
                return res;
            }
//5546. 按键持续时间最长的键
            char slowestKey(std::vector<int> &releaseTimes, std::string keysPressed){
                std::vector<int> mp(26);
                mp[keysPressed[0] - 'a'] = releaseTimes[0];
                int len = keysPressed.size();
                for(int i=1; i<len; ++i){
                    mp[keysPressed[i]-'a'] = std::max(mp[keysPressed[i]-'a'], releaseTimes[i] - releaseTimes[i-1]);
                }
                int ans, max_ = 0;
                for(int i=25; i>=0; --i){
                    if(mp[i] > max_)ans = i+'a', max_ = mp[i];
                }
                return ans;
            }
    };
};
namespace WK211{
    class Solution{
        public:
//5128. 带阈值的图连通性
            std::vector<bool> areConnected(int n, int threshold, std::vector<std::vector<int>> &queries){
                std::vector<int> _f(n+1);
                std::iota(begin(_f), end(_f), 0);
                std::function<int(int)> _find = [&](int a){
                    return _f[a] == a ? a : _f[a] = _find(_f[a]);
                };
                std::function<void(int, int)> _union = [&](int a, int b){
                    int p1 = _find(a), p2 = _find(b);
                    if(p1 != p2)_f[p2]  = p1;
                };
                for(int z=threshold+1; z<=n; ++z){
                    for(int p=z,q=2*z; q<=n; p+=z, q+=z){
                        _union(p, q);
                    }
                }
                std::vector<bool> res;
                for(auto &q : queries){
                    res.push_back(_find(q[0]) == _find(q[1]));
                }
                return res;
            }
//5545. 无矛盾的最佳球队
            int bestTeamScore(std::vector<int> &scores, std::vector<int> &ages){
                std::vector<std::pair<int, int>> sa;
                int len = scores.size();
                for(int i=0; i<len; ++i){
                    sa.emplace_back(scores[i], ages[i]);
                }
                std::sort(begin(sa), end(sa), [&](auto &a, auto &b){
                    return a.second == b.second ? a.first < b.first : a.second< b.second; });
                std::vector<int> dp(len);
                int res = 0, sc, age;
                for(int i=0; i<len; ++i){
                    dp[i] = sc = sa[i].first, age = sa[i].second;
                    for(int j=0; j<i; ++j){
                        if(sc >= sa[j].first){
                            dp[i] = std::max(dp[i], dp[j] + sc);
                        }
                    }
                    res = std::max(res, dp[i]);
                }
                return res;
            }
//5544. 执行操作后字典序最小的字符串
            std::string findLexSmallestString(std::string s, int a, int b){
                std::set<std::string> mp;
                int len = s.size();
                std::function<void(std::string &)> _dfs
                    = [&](std::string &str){
                        if(!mp.insert(str).second)return;
                        std::string t1 = str, t2;
                        for(int i=1; i<len; i+=2){
                            t1[i] = ((t1[i] - '0' + a) % 10) + '0';
                        }
                        _dfs(t1);
                        t2 = str.substr(len - b) + str.substr(0, len - b);
                        _dfs(t2);
                    };
                _dfs(s);
                return *mp.begin();
            }
            int maxLengthBetweenEqualCharacyers(std::string s){
                std::unordered_map<int, int> mp;
                int res = -1, len = s.size();
                for(int i=0; i<len; ++i){
                    if(mp.count(s[i])){
                        res = std::max(res, i - mp[s[i]] - 1);
                    }else{
                        mp[s[i]] = i;
                    }
                }
                return res;
            }
    };
};
namespace WK210{
    class Solution{
        public:
//5538. 统计子树中城市之间最大距离
            std::vector<int> countSubgrouphsForEachDiameter_dp(int n,
                    std::vector<std::vector<int>> &edges){
                std::vector<std::vector<int>> e(n, std::vector<int>(n, 0));
                std::vector<std::vector<int>> d(n, std::vector<int>(n, 10000));
                for(auto &p : edges){
                    e[p[0]-1][p[1]-1] = e[p[1]-1][p[0]-1] = 1;
                    d[p[0]-1][p[1]-1] = d[p[1]-1][p[0]-1] = 1;
                    d[p[0]-1][p[0]-1] = d[p[1]-1][p[1]-1] = 0;
                }
                for(int i=0; i<n; ++i){
                    for(int j=0; j<n; ++j){
                        for(int k=0; k<n; ++k){
                            d[j][k] = std::min(d[j][k], d[j][i] + d[i][k]);
                        }
                    }
                }
                std::vector<int> dp(1<<n, INT_MAX);
                dp[0] = 0;
                for(int i=1; i<(1<<n); ++i){
                    for(int j=0; j<n; ++j){
                        if(!(i&(1<<j)))continue;
                        int pre = i ^ (1<<j);
                        if(dp[pre] == INT_MAX)continue;
                        if(!pre){
                            dp[i] = 0;
                            break;
                        }else{
                            int max_d = INT_MIN;
                            int _flag = 0;
                            for(int k=0; k<n; ++k){
                                if(i==k || !(i&(1<<k)))continue;
                                if(e[j][k])_flag = 1;
                                max_d = std::max(max_d, d[j][k]);
                            }
                            if(_flag){
                                dp[i] = std::max(max_d, dp[pre]);
                                break;
                            }
                        }
                    }
                }
                std::vector<int> res(n-1);
                for(int i=1; i<(1<<n); ++i){
                    if(dp[i]>0 && dp[i]<INT_MAX)++res[dp[i]-1];
                }
                return res;
            }
            std::vector<int> countSubgrouphsForEachDiameter(int n,
                    std::vector<std::vector<int>> &edges){
                std::vector<std::vector<int>> e(n+1);
                for(auto &p : edges){
                    e[p[0]].push_back(p[1]);
                    e[p[1]].push_back(p[0]);
                }
                std::function<void(std::bitset<16> &, int &, int &, int &)> _bfs
                    = [&](std::bitset<16> &bs, int &sn, int &slc, int &di){
                    std::vector<int> vi(n+1);
                    std::queue<int> q;
                    q.push(sn);
                    vi[sn] = 1;
                    while(q.size()){
                        int size = q.size();
                        slc += size;
                        ++di;
                        for(int i=0; i<size; ++i){
                            sn = q.front();q.pop();
                            for(auto &x : e[sn]){
                                if(!vi[x] && bs[x-1]){
                                    vi[x] = 1;
                                    q.push(x);
                                }
                            }
                        }
                    }
                };
                std::vector<int> res(n-1);
                for(int i=1; i<(1<<n); ++i){
                    std::bitset<16> bs(i);
                    int cnt = bs.count();
                    if(cnt < 2)continue;
                    int s_n;
                    for(int j=0; j<n; ++j){
                        if(bs[j]){
                            s_n = j + 1;
                            break;
                        }
                    }
                    int s_l_c = 0, di = -1;
                    _bfs(bs, s_n, s_l_c, di);
                    if(s_l_c != cnt)continue;
                    s_l_c = 0, di = -1;
                    _bfs(bs, s_n, s_l_c, di);
                    ++res[di-1];
                }
                return res;
            }
//1616. 分割两个字符串得到回文串
            bool checkPalindromeFormation(std::string a, std::string b){
                std::function<bool(std::string)> _check = [&](std::string s){
                    int l = 0, r = s.size() - 1;
                    while(l < r){
                        if(s[l++] != s[r--])return false;
                    }
                    return true;
                };
                int len = a.size();
                int l = 0, r = len - 1;
                while(l<r && a[l]==b[r])++l, --r;
                if(_check(a.substr(l, r-l+1)) ||
                        _check(b.substr(l, r-l+1))) return true;
                l = 0, r = len - 1;
                while(l<r && a[r]==b[l])++l, --r;
                return _check(a.substr(l, r-l+1)) || _check(b.substr(l, r-l+1));
            }
            bool checkPalindromeFormation_better(std::string a, std::string b){
                int len = a.size();
                std::function<bool(std::string &, std::string &)> _check
                    = [&](std::string &x, std::string &y){
                        int _f = 1;
                        for(int i=0; i<len/2; ++i){
                            if(_f && x[i] != y[len-i-1])_f = 0;
                            if(!_f && x[i] != x[len-i-1])return false;
                        }
                        return true;
                    };
                if(_check(a, b) || _check(b, a))return true;
                std::reverse(begin(a), end(a));
                std::reverse(begin(b), end(b));
                return _check(a, b) || _check(b, a);
            }
//5536. 最大网络秩
            int maxmalNetworkRank(int n, std::vector<std::vector<int>> &roads){
                std::vector<std::unordered_set<int>> G(n);
                for(auto &p : roads){
                    G[p[0]].insert(p[1]);
                    G[p[1]].insert(p[0]);
                }
                int res = 0;
                for(int i=0; i<n; ++i){
                    int t = G[i].size();
                    for(int j=i+1; j<n; ++j){
                        res = std::max(res, (int)(t + G[j].size() - G[j].count(i)));
                    }
                }
                return res;
            }
//5535. 括号的最大嵌套深度
            int maxDepth(std::string s){
                int l = 0, res = 0, len = s.size();
                for(auto &c : s){
                    if(c=='('){
                        if(++l > res)res = l;
                    }else if(c==')'){
                        --l;
                    }
                }
                return res;
            }
    };
};
namespace WK209{
    class Solution{
        public:
//5533. 使整数变为 0 的最少操作次数
            int miniumOneBitOperators(int n){
                std::vector<int> cnt(32);
                int res = 0;
                for(int i=1; i<31; ++i)cnt[i-1] = (1<<i) - 1;
                while(n){
                    int i = -1, j = -1;
                    for(int k=30; k>=0; --k){
                        if((1<<k)&n){
                            if(i==-1){
                                i = k;
                            }else if(j==-1){
                                j = k;
                            }else{
                                break;
                            }
                        }
                    }
                    n ^= (1<<i);
                    if(j==-1){
                        res += cnt[i];
                    }else{
                        n ^= (1<<j);
                        res += (cnt[i] - cnt[j]);
                    }
                }
                return res;
            }
//1610. 可见点的最大数目
            int visiblePoints(std::vector<std::vector<int>> &points, int angle, std::vector<int> &location){
                const double ESP = 1e-8;
                std::map<double, int> mp;
                int x = location[0];
                int y = location[1];
                std::vector<double> v;
                int same = 0;
                for(auto &p : points){
                    int x1 = p[0], y1 = p[1];
                    if(x1==x && y1==y){
                        ++same;
                    }else{
                        v.emplace_back(atan2(y1-y, x1-x)*180/M_PI);
                    }
                }
                std::sort(begin(v), end(v));
                int m = v.size();
                for(int i=0; i<m; ++i)v.emplace_back(360+v[i]);
                int r = 0, res = 0;
                for(int l=0; l<m; ++l){
                    while(r+1<m*2 && v[r+1]-v[l] <= (double)(angle+ESP))++r;
                    res = std::max(res, r-l+1);
                }
                return res + same;
            }
//5532. 奇偶树
            bool isEvenOddTree(TreeNode *root){
                if(!root)return false;
                std::queue<TreeNode *> q;
                std::function<bool(int, int)> _can = [&](int size, int l){
                    int pre = INT_MIN;
                    for(int i=0; i<size; ++i){
                        auto cur = q.front();q.pop();
                        if(pre>=cur->val || (l&1)==(cur->val&1))return false;
                        pre = cur->val;
                        if(cur->left){
                            if(!(l&1))cur->left->val *= -1;
                            q.push(cur->left);
                        }
                        if(cur->right){
                            if(!(l&1))cur->right->val *= -1;
                            q.push(cur->right);
                        }
                    }
                    return true;
                };
                q.push(root);
                int l = -1;
                while(q.size()){
                    if(!_can(q.size(), ++l))return false;
                }
                return true;
            }
            int specialArray(std::vector<int> &nums){
                std::sort(nums.begin(), nums.end());
                int j = 0;
                for(int i=0; i<nums.back(); ++i){
                    auto pos = lower_bound(nums.begin(), nums.end(), i);
                    if(nums.end() - pos == i)return i;
                }
                return -1;
            }
    };
};
class ThroneInheritance {
//5525. 皇位继承顺序
public:
    std::string King;
    std::unordered_set<std::string> dead;
    std::unordered_map<std::string, std::vector<std::string>> ft;
    std::unordered_map<std::string, std::string> pa;
    std::vector<std::string> help;
    int old_size;
    ThroneInheritance(std::string kingName) {
        King = kingName;
        ft[King] = {};
    }
    void birth(std::string parentName, std::string childName) {
        ft[parentName].push_back(childName);
        pa[childName] = parentName;
    }
    void death(std::string name) {
        dead.insert(name);
    }
    std::string Successor(std::string &name, std::unordered_set<std::string> &ans){
        auto ch = ft[name];
        for(auto p : ch){
            if(!ans.count(p)){
                ans.insert(p);
                help.push_back(p);
                return p;
            }
        }
        if(name==King)return "";
        return Successor(pa[name], ans);
    }
    void _dfs(std::string &w, std::vector<std::string> &ans){
        if(!dead.count(w))ans.push_back(w);
        for(auto &s : ft[w])_dfs(s, ans);
    }
    std::vector<std::string> getInheritanceOrder() {
        std::vector<std::string> res;
        _dfs(King, res);
        return res;
    }
    std::vector<std::string> getInheritanceOrder_fuck() {
        std::vector<std::string> res;
        if(old_size==pa.size()){
            for(auto p : help)if(!dead.count(p))res.push_back(p);
            return res;
        }
        old_size = pa.size();
        std::unordered_set<std::string> ans;
        ans.insert(King);
        help.clear();
        help.push_back(King);
        std::string temp = King;
        while(((temp=Successor(temp, ans)).size()));
        for(auto p : help)if(!dead.count(p))res.push_back(p);
        return res;
    }
};
class Solution{
    public:
//---------------------------------------------208
//5526. 最多可达成的换楼请求数目
        int maximumRrequests(int n, std::vector<std::vector<int>> &requests){
            int res = 0;
            int size = requests.size();
            std::function<int(int)> _calc = [&](int state){
                if(res > __builtin_popcount(state))return -1;
                std::vector<int> in(n);
                std::vector<int> out(n);
                int ans = 0;
                for(int i=0; i<size; ++i){
                    if(!(state&(1<<i)))continue;
                    ++out[requests[i][0]];
                    ++in[requests[i][1]];
                    ++ans;
                }
                for(int i=0; i<n; ++i){
                    if(in[i] != out[i])return -1;
                }
                return ans;
            };
            for(int state=0; state<(1<<size); ++state){
                res = std::max(res, _calc(state));
            }
            return res;
        }
//5524. 经营摩天轮的最大利润
        int minOperationsMaxProfit(std::vector<int> &customers, int boardingCost, int runningCost){
            if(boardingCost*4 < runningCost)return -1;
            int res  = -1;
            int n    = customers.size();
            int wait = 0;
            int i    = 0;
            int up   = 0;
            int maxp = INT_MIN;
            int p = 0;
            while(i<n || wait){
                if(i<n)wait += customers[i];
                if(wait){
                    up = std::min(4, wait);
                    wait -= up;
                    p += up*boardingCost;
                }
                p -= runningCost;
                if(maxp <  p){
                    maxp = p;
                    if(maxp > 0)res = i + 1;
                }
                ++i;
            }
            return res;
        }
//5523. 文件夹操作日志搜集器
        int minOperatations(std::vector<std::string> &logs){
            int res = 0;
            for(auto &x : logs){
                if(x=="./")continue;
                if(x=="../"){
                    res-=res!=0;
                }else{
                    ++res;
                }
            }
            return res;
        }
//---------------------------------------------207
        int connectTwograph(std::vector<std::vector<int>> &cost){
            int m = cost.size();
            int n = cost[0].size();
            std::vector<int> dp_0((1<<n), INT_MAX);
            std::vector<int> dp_1((1<<n), INT_MAX);
            std::vector<std::vector<int>> sums(m, std::vector<int>((1<<n), 0));
            for(int i=0; i<m; ++i){
                for(int j=0; j<(1<<n); ++j){
                    int sum = 0;
                    for(int k=0; k<n; ++k){
                        if(j&(1<<k))sum += cost[i][k];
                    }
                    sums[i][j] = sum;
                }
            }
            dp_0 = sums[0];
            for(int i=1; i<m; ++i){
                for(int j=1; j<(1<<n); ++j){
                    for(int k=0; k<n; ++k){
                        dp_1[j|(1<<k)] = std::min(dp_1[j|(1<<k)], dp_0[j]+sums[i][(1<<k)]);
                    }
                    int rest = ((1<<n) - 1) ^ j;
                    for(int k=rest; k>=1; k=rest&(k-1)){
                        dp_1[j|k] = std::min(dp_1[j|k], dp_0[j]+sums[i][k]);
                    }
                }
                dp_0 = dp_1;
                std::fill(dp_1.begin(), dp_1.end(), INT_MAX);
            }
            return dp_0[(1<<n)-1];
            //for(int i=1; i<m; ++i){
                //for(int j=1; j<(1<<n); ++j){
                    //for(int k=1; k<(1<<n); ++k){
                        //dp_1[j|k] = std::min(dp_1[j|k], dp_0[k]+sums[i][j]);
                    //}
                //}
                //dp_0 = dp_1;
                //std::fill(dp_1.begin(), dp_1.end(), INT_MAX);
            //}
            //return dp_0[(1<<n)-1];
        }
        int  maxProductPath(std::vector<std::vector<int>> &grid){
            int MOD = 1e9 + 7;
            int m   = grid.size();
            int n   = grid[0].size();
            std::vector<std::vector<long long>> dp_0(m, std::vector<long long>(n, 0));
            std::vector<std::vector<long long>> dp_1(m, std::vector<long long>(n, 0));
            dp_0[0][0] = dp_1[0][0] = grid[0][0];
            for(int i=1; i<m; ++i)dp_0[i][0] = dp_1[i][0] = grid[i][0] * dp_0[i-1][0];
            for(int i=1; i<n; ++i)dp_0[0][i] = dp_1[0][i] = grid[0][i] * dp_0[0][i-1];
            for(int i=1; i<m; ++i){
                for(int j=1; j<n; ++j){
                    if(grid[i][j] > 0){
                        dp_0[i][j] = std::max(dp_0[i-1][j], dp_0[i][j-1])*static_cast<long long>(grid[i][j]);
                        dp_1[i][j] = std::min(dp_1[i-1][j], dp_1[i][j-1])*static_cast<long long>(grid[i][j]);
                    }else if(grid[i][j] < 0){
                        dp_1[i][j] = std::max(dp_0[i-1][j], dp_0[i][j-1])*static_cast<long long>(grid[i][j]);
                        dp_0[i][j] = std::min(dp_1[i-1][j], dp_1[i][j-1])*static_cast<long long>(grid[i][j]);
                    }
                }
            }
            return dp_0[m-1][n-1]>=0?dp_0[m-1][n-1] % MOD:-1;
        }

        int maxUniqueSplit_shuwei_dp(std::string s){
            int res = -1;
            int n   = s.length();
            std::unordered_set<std::string> mp;
            for(int state=0; state<(1<<n); ++state){
                if(res > __builtin_popcount(state))continue;
                for(int i=0, b=0; i<n; ++i){
                    if(state&(1<<i) || (i==n-1)){
                        if(!mp.insert(s.substr(b, i-b+1)).second)break;
                        b = i + 1;
                    }
                }
                res = std::max(res, (int)mp.size());
                mp.clear();
            }
            return res;
        }
        int maxUniqueSplit(std::string s){
            int res = -1;
            std::unordered_set<std::string> mp;
            std::function<void(std::string&, int)> _dfs = [&](std::string &ans, int i){
                if(res>mp.size()+s.length()-i)return;
                if(i==s.length()){
                    res = std::max(res, (int)mp.size());
                    return;
                }
                std::string temp;
                for(int k=i; k<s.length(); ++k){
                    temp += s[k];
                    if(mp.count(temp))continue;
                    mp.insert(temp);
                    _dfs(temp, k+1);
                    mp.erase(temp);
                }
            };
            std::string ans;
            _dfs(ans, 0);
            return res;
        }
        std::string reorderSpaces(std::string text){
            int b = 0;
            int w = 0;
            for(auto &c : text)b += c==' ';
            std::stringstream tmp;
            tmp << text;
            std::vector<std::string> ss;
            while(tmp >> text)ss.push_back(text);
            if(ss.size()==1)return ss.back() + std::string(b, ' ');
            int add = b / (ss.size()-1);
            int lef = b % (ss.size()-1);
            std::string bl(add, ' ');
            std::string ll(lef, ' ');
            std::string res;
            for(int i=0; i<ss.size()-1; ++i)res += ss[i] + bl;
            return res + ss.back() + ll;
        }
};
int main(int argc,const char *argv[]){
    WE215::Solution te;
    int m = 5, n = 5, i = 6, e = 6;
    //int m = 4, n = 4, i = 3, e = 2;
    //std::cout<<te.getMaxGridHappiness_fuck(m, n, i, e)<<std::endl;
    //std::cout<<te.getMaxGridHappiness(m, n, i, e)<<std::endl;

    return 0;
}

/*********************************************
*     ------------------------
*     ------------------------
*     file name: some_arr_pro.cpp
*     author   : @ JY
*     date     : 2020--06--24
**********************************************/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <numeric>
#include <sstream>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

class Solution{
    public:
//面试题 08.04. 幂集
        std::vector<std::vector<int>> subsets(std::vector<int> &nums){
            std::vector<std::vector<int>> res;
            int len = nums.size();
            std::function<void(int, std::vector<int> &arr)> _dfs
                = [&](int i, std::vector<int> &arr){
                    res.push_back(arr);
                    for(int j=i; j<len; ++j){
                        if(j>i && nums[j] == nums[j-1])continue;
                        arr.push_back(nums[j]);
                        _dfs(j+1, arr);
                        arr.pop_back();
                    }
                };
            std::vector<int> arr;
            std::sort(begin(nums), end(nums));
            _dfs(0, arr);
            return res;
        }
//950. 按递增顺序显示卡牌
        std::vector<int> deckRevedIncreasing_better(std::vector<int> &deck){
            int len = deck.size();
            std::vector<int> vi(len), res(len);
            std::sort(begin(deck), end(deck));
            std::function<int(int)> _next = [&](int i){
                for(int j=i; j<len; ++j)if(!vi[j])return j;
                for(int j=0; j<i; ++j)if(!vi[j])return j;
                return -1;
            };
            for(int i=0, j=-1; ~i; i=_next(_next(i+1)+1)){
                res[i] = deck[++j];
                vi[i]  = 1;
            }
            return res;
        }
        std::vector<int> deckRevedIncreasing(std::vector<int> &deck){
            int len = deck.size();
            std::vector<int> res(len);
            std::deque<int> st;
            for(int i=0; i<len; ++i)st.push_back(i);
            std::sort(begin(deck), end(deck));
            for(auto &x : deck){
                res[st.front()] = x;
                st.pop_front();
                if(st.size()){
                    st.push_back(st.front());
                    st.pop_front();
                }
            }
            return res;
        }
//915. 分割数组
        int partitionDisjoint(std::vector<int> &A){
            int len = A.size(), res = 0, max_ = A[0], lm = max_;
            for(int i=0; i<len; ++i){
                lm = std::max(lm, A[i]);
                if(A[i] >= max_)continue;
                res  = i;
                max_ = lm;
            }
            return ++res;
        }
//1222. 可以攻击国王的皇后
        std::vector<std::vector<int>> queensAttacktheKing(
                std::vector<std::vector<int>> &queens,
                std::vector<int> &king){
            std::vector<std::vector<int>> res;
            int x = king[0], y = king[1];
            std::vector<int> _fun {1, 0, 1, -1, 0, -1, -1, 1, 1};
            std::vector<int> _e(64);
            for(auto &p : queens)_e[p[0]*8 + p[1]] = 1;
            for(int f=0; f<8; ++f){
                int i = x + _fun[f];
                int j = y + _fun[f+1];
                while(i>=0 && j>=0 && i<8 && j<8){
                    if(_e[i * 8 + j]){
                        res.push_back({i, j});
                        break;
                    }
                    i += _fun[f];
                    j += _fun[f+1];
                }
            }
            return res;
        }
//1035. 不相交的线
        int maxUncrossedLines_better(std::vector<int> &A, std::vector<int> &B){
            int len1 = A.size(), len2 = B.size(), pre, temp;
            std::vector<int> dp(len2+1);
            for(int i=0; i<len1; ++i){
                pre = 0, temp = 0;
                for(int j=1; j<=len2; ++j){
                    temp  = dp[j];
                    dp[j] = std::max(dp[j], dp[j-1]);
                    if(A[i] == B[j-1]){
                        dp[j] = std::max(dp[j], pre + 1);
                    }
                    pre = temp;
                }
            }
            return dp[len2];
        }
        int maxUncrossedLines(std::vector<int> &A, std::vector<int> &B){
            int len1 = A.size(), len2 = B.size();
            std::vector<std::vector<int>> dp(len1+1, std::vector<int>(len2+1));
            dp[0][0] = 1;
            for(int i=1; i<=len1; ++i){
                for(int j=1; j<=len2; ++j){
                    dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
                    if(A[i-1] == B[j-1]){
                        dp[i][j] = std::max(dp[i][j], dp[i-1][j-1] + 1);
                    }
                }
            }
            return dp[len1][len2];
        }
//611. 有效三角形的个数
        int triangleNumber(std::vector<int> &nums){
            std::sort(begin(nums), end(nums));
            int len = nums.size(), res = 0;
            for(int i=0; i<len-2; ++i){
                if(!nums[i])continue;
                for(int j=i+1, k=j+1; j<len-1; ++j){
                    while(k<len && nums[i] + nums[j] > nums[k])++k;
                    res += k - j - 1;
                }
            }
            return res;
        }
//962. 最大宽度坡
        int maxWIdthRamp_better(std::vector<int> &A){
            int len = A.size(), res = 0;
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                if(!st.size() || A[i] < A[st.top()])st.emplace(i);
            }
            for(int i=len-1; i>res; --i){
                while(st.size() && A[i] >= A[st.top()]){
                    res = std::max(res, i - st.top());
                    st.pop();
                }
            }
            return res;
        }
        int maxWIdthRamp(std::vector<int> &A){
            int len = A.size(), res = 0, min_ = len;
            std::vector<int> mp(len);
            std::iota(begin(mp), end(mp), 0);
            std::sort(begin(mp), end(mp), [&](int i, int j){
                return A[i]==A[j] ? i < j : A[i] < A[j]; });
            for(auto &x : mp){
                res  = std::max(res, x - min_);
                min_ = std::min(min_, x);
            }
            return res;
        }
//90. 子集 II
        std::vector<std::vector<int>> subsetsWithDup_better(std::vector<int> &nums){
            int len = nums.size();
            std::vector<std::vector<int>> res;
            std::function<void(std::vector<int> &arr, int i)> _dfs
                = [&](std::vector<int> &arr, int i){
                    res.push_back(arr);
                    for(int j=i; j<len; ++j){
                        if(j>i && nums[j] == nums[j-1])continue;
                        arr.push_back(nums[j]);
                        _dfs(arr, j+1);
                        arr.pop_back();
                    }
            };
            std::sort(begin(nums), end(nums));
            std::vector<int> arr;
            _dfs(arr, 0);
            return res;
        }
        std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums){
            int len = nums.size();
            std::set<std::vector<int>> ans;
            std::function<void(int, std::vector<int> &arr)> _dfs
                = [&](int i, std::vector<int> &arr){
                    if(i == len){
                        ans.insert(arr);
                        return;
                    }
                    arr.push_back(nums[i]);
                    _dfs(i+1, arr);
                    arr.pop_back();
                    _dfs(i+1, arr);
            };
            std::vector<int> arr;
            _dfs(0, arr);
            std::set<std::vector<int>> temp;
            for(auto vi : ans){
                std::sort(begin(vi), end(vi));
                temp.insert(vi);
            }
            std::vector<std::vector<int>> res(begin(temp), end(temp));
            return res;
        }
//1437. 是否所有 1 都至少相隔 k 个元素
        bool kLengthApart(std::vector<int> &nums, int k){
            int b = -1, len = nums.size();
            for(int i=0; i<len; ++i){
                if(nums[i]){
                    if(b!=-1 && i - b - 1 < k){
                        return false;
                    }
                    b = i;
                }
            }
            return true;
        }
//667. 优美的排列 II
        std::vector<int> constructArray(int n, int k){
            std::vector<int> res(n);
            for(int i=0,t=0; i<=k; i+=2)res[i] = ++t;
            for(int i=1,t=k+2; i<=k; i+=2)res[i] = --t;
            for(int i=k+1; i<n; ++i)res[i] = i + 1;
            return res;
        }
//1233. 删除子文件夹
        std::vector<std::string> removeSubfolders(std::vector<std::string> &folder){
            if(!folder.size())return {};
            std::sort(begin(folder), end(folder));
            std::vector<std::string> res {folder[0]};
            int len = folder.size();
            for(int i=1; i<len; ++i){
                if(folder[i].compare(0, res.back().size(), res.back()) ||
                        folder[i][res.back().size()] != '/'){
                    res.push_back(folder[i]);
                }
            }
            return res;
        }

//1007. 行相等的最少多米诺旋转
        int minDomimaRprations_btter(std::vector<int> &A, std::vector<int> &B){
            int len = A.size();
            std::vector<int> cnt(7);
            for(int i=0; i<len; ++i)++cnt[A[i]], ++cnt[B[i]];
            int num = -1;
            for(int i=0; i<7; ++i){
                if(cnt[i] >= len)num = i;
            }
            if(num == -1)return -1;
            int a = 0 , ab = 0;
            for(int i=0; i<len; ++i){
                if(A[i]==B[i] && A[i] == num){
                    ++ab;
                }else if(A[i] != num && B[i] != num){
                    return -1;
                }else if(A[i] == num){
                    ++a;
                }
            }
            return std::min(a, len - a - ab);
        }
        int minDomimaRprations(std::vector<int> &A, std::vector<int> &B){
            std::unordered_map<int, int> mp1, mp2;
            for(auto &x : A)++mp1[x];
            for(auto &x : B)++mp2[x];
            std::vector<std::pair<int, int>> p1(begin(mp1), end(mp1)),
                                             p2(begin(mp2), end(mp2));
            std::sort(begin(p1), end(p1), [&](auto &a, auto &b){
                    return a.second > b.second; });
            std::sort(begin(p2), end(p2), [&](auto &a, auto &b){
                    return a.second > b.second; });
            int i = 0, j = 0, len = A.size(), ans = 0, s1 = p1.size(), s2=p2.size();
            while(i<s1 && j<s2){
                int f = 1, z = 0, ans = 0;
                int k = p1[i].second > p2[j].second ? (p1[i++].first): (f=0, p2[j++].first);
                auto arr1 = A, arr2 = B;
                if(!f)std::swap(arr1, arr2);
                for(; z<len; ++z){
                    if(arr1[z] != k){
                        if(arr2[z] != k)break;
                        ++ans;
                    }
                }
                if(z==len)return ans;
            }
            return -1;
        }
//795. 区间子数组个数
        int numSubarrayBoundedMax_st(std::vector<int> &A, int L, int R){
            int len = A.size(), res = 0;
            std::vector<int> l(len, -1), r(len, len);
            std::stack<int> st;
            for(int i=0; i<len; ++i){
                while(st.size() && A[st.top()] < A[i]){
                    r[st.top()] = i;
                    st.pop();
                }
                st.push(i);
            }
            st = {};
            for(int i=len-1; ~i; --i){
                while(st.size() && A[i] >= A[st.top()]){
                    l[st.top()] = i;
                    st.pop();
                }
                st.push(i);
            }
            for(int i=0; i<len; ++i){
                if(A[i] < L || A[i] > R)continue;
                res += (i - l[i]) * (r[i] - i);
            }
            return res;
            //for(auto &x : l)std::cout<<x<<"   ";
            //std::cout<<std::endl;
            //for(auto &x : r)std::cout<<x<<"   ";
        }

        int numSubarrayBoundedMax(std::vector<int> &A, int L, int R){
            int len = A.size();
            std::function<int(int)> _count = [&](int limit){
                int ans = 0, cnt = 0;
                for(auto &x : A){
                    cnt = x<=limit ? cnt + 1 : 0;
                    ans += cnt;
                }
                return ans;
            };
            return _count(R) - _count(L-1);
        }
//825. 适龄的朋友
        int numFriendRequests(std::vector<int> &ages){
            int res = 0;
            std::vector<int> cnt(121);
            for(auto &x : ages)++cnt[x];
            for(int i=0; i<121; ++i){
                int cnt1 = cnt[i];
                for(int j=(i>>1) + 8; j<=i; ++j){
                    res += (cnt1 - (j==i)) * cnt[j];
                }
            }
            return res;
        }
//565. 数组嵌套
        int arrayNesting(std::vector<int> &nums){
            int len = nums.size();
            std::vector<int> _f(len), _n(len, 1);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i] == i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                int pa = _find(a), pb = _find(b);
                if (pa == pb) return;
                _f[pa] = pb;
                _n[pb] += _n[pa];
                _n[pa] = 0;
            };
            for(int i=0; i<len; ++i)_union(i, nums[i]);
            return *std::max_element(begin(_n), end(_n));
        }
        int arrayNesting_fuck(std::vector<int> &nums){
            int len = nums.size(), res = 0;
            std::vector<int> vi(len, -1);
            std::function<int(int)> _dfs = [&](int index){
                if(vi[index] != -1)return 0;
                vi[index] = 1;
                return 1 + _dfs(nums[index]);
            };
            for(int i=0; i<len; ++i){
                res = std::max(res, _dfs(nums[i]));
            }
            return res;
        }

//768. 最多能完成排序的块 II
        int maxChunksToSortedII_better(std::vector<int> &arr){
            std::stack<int> st;
            for(auto &x : arr){
                if(st.size() && x < st.top()){
                    int head = st.top();
                    while(st.size() && x < st.top())st.pop();
                    st.push(head);
                }else{
                    st.push(x);
                }
            }
            return st.size();
        }
        int maxChunksToSortedII(std::vector<int> &arr){
            int len = arr.size(), res = 1;
            std::vector<int> l(len), r(len);
            l[0] = arr[0], r[len-1] = arr[len-1];
            for(int i=1; i<len; ++i){
                l[i] = std::max(arr[i], l[i-1]);
                r[len-i-1] = std::min(arr[len-i-1], r[len-i]);
            }
            for(int i=0; i<len-1; ++i){
                res += l[i] <= r[i+1];
            }
            return res;
        }
//769. 最多能完成排序的块
        int maxChunksToSortedI(std::vector<int> &arr){
            int res = 0, max_ = INT_MIN, len = arr.size();
            for(int i=0; i<len; ++i)res += i==(max_=std::max(max_, arr[i]));
            return res;
        }
//1177. 构建回文串检测
        std::vector<bool> canMakePaliQueries_better(std::string s, std::vector<std::vector<int>> &queries){
            int cur = 0, len = queries.size();
            std::vector<int> state;
            for(auto &c : s){
                state.push_back(cur ^= (1<<(c-'a')));
            }
            std::vector<bool> res(len);
            for(int i=0; i<len; ++i){
                int l = queries[i][0], k = queries[i][2];
                int z = state[queries[i][1]] ^ (l ?  state[l-1] : 0);
                if((k<<1) + 1 < __builtin_popcount(z))continue;
                res[i] = true;
            }
            return res;
        }
        std::vector<bool> canMakePaliQueries(std::string s, std::vector<std::vector<int>> &queries){
            int len = s.size(), size = queries.size();
            std::vector<std::vector<int>> cnt(len, std::vector<int>(26));
            cnt[0][s[0]-'a'] = 1;
            for(int i=1; i<len; ++i){
                cnt[i] = cnt[i-1];
                ++cnt[i][s[i]-'a'];
            }
            std::vector<bool> res(size);
            for(int i=0; i<size; ++i){
                auto &q = queries[i];
                int l   = q[0], r = q[1], k = q[2], index = 0;
                std::vector<int> fre = cnt[r];
                if(l)while(index<26)fre[index] -= cnt[l-1][index],++index;
                int eve = 0;
                for(auto &x : fre)eve += (x&1);
                if((k<<1) + 1 < eve)continue;
                res[i] = true;
            }
            return res;
        }
//1169. 查询无效交易
        std::vector<std::string> invalidTransactions(std::vector<std::string> &transactions){
            std::unordered_map<std::string, std::vector<int>> mp;
            int len = transactions.size();
            std::stringstream ss;
            std::string temp, t1, s1, l1, t2, s2, l2;
            for(int i=0; i<len; ++i){
                ss.clear();
                ss.str(transactions[i]);
                std::getline(ss, temp, ',');
                mp[temp].push_back(i);
            }
            std::unordered_set<int> ans;
            for(auto &[str, st] : mp){
                int size = st.size();
                for(int i=0; i<size; ++i){
                    ss.clear();
                    ss.str(transactions[st[i]]);
                    std::getline(ss, temp, ',');
                    std::getline(ss, t1, ',');
                    std::getline(ss, s1, ',');
                    std::getline(ss, l1, ',');
                    if(std::stoi(s1) > 1000)ans.insert(st[i]);
                    for(int j=i+1; j<size; ++j){
                        ss.clear();
                        ss.str(transactions[st[j]]);
                        std::getline(ss, temp, ',');
                        std::getline(ss, t2, ',');
                        std::getline(ss, s2, ',');
                        std::getline(ss, l2, ',');
                        if(std::stoi(s2) > 1000)ans.insert(st[j]);
                        if(!l1.compare(l2))continue;
                        if(std::abs(std::stoi(t1) - std::stoi(t2)) > 60)continue;
                        ans.insert(st[i]);
                        ans.insert(st[j]);
                    }
                }
            }
            std::vector<std::string> res;
            for(auto &i : ans)res.push_back(transactions[i]);
            return res;
        }
//1296. 划分数组为连续数字的集合
        bool isPossibleDivide(std::vector<int> &nums, int k){
            std::map<int, int> mp;
            for(auto &x : nums)++mp[x];
            for(auto &[num, n] : mp){
                if(n > 0){
                    for(int i=num+1; i<num+k; ++i){
                        if((mp[i] -= n) < 0)return false;
                    }
                }
            }
            return true;
        }
//面试题 16.22. 兰顿蚂蚁
        std::vector<std::string> printKMoves(int K){
            std::unordered_map<int, std::unordered_set<int>> mp1;
            std::unordered_map<char, int> mp2 = {{'L', 0}, {'U', 1}, {'R', 2}, {'D', 3}};
            std::vector<int> _fun = {-1, 0, 1, 0, -1};
            int x = 0, y = 0, l = 0, r = 0, d = 0, u = 0, f = 2;
            std::string _fs = "LURD";
            while(K--){
                if(mp1.count(x) && mp1[x].count(y)){
                    mp1[x].erase(y);
                    x -= _fun[mp2[_fs[f]]];
                    y -= _fun[mp2[_fs[f]]+1];
                    f = (f+3) % 4;
                }else{
                    mp1[x].insert(y);
                    x += _fun[mp2[_fs[f]]];
                    y += _fun[mp2[_fs[f]]+1];
                    f = (f+1) % 4;
                }
                l = std::min(l, y), r = std::max(r, y);
                u = std::min(u, x), d = std::max(d, x);
            }
            int m = d - u + 1, n = r - l + 1;
            std::vector<std::string> res(m, std::string(n, '_'));
            for(auto &&[i, js] : mp1){
                for(auto &j : js)res[i-u][j-l] = 'X';
            }
            res[x-u][y-l] = _fs[f];
            return res;
        }
//1109. 航班预订统计
        std::vector<int> corpFlightBookings(std::vector<std::vector<int>> &bookings, int n){
            std::vector<int> res(n+1);
            for(auto &p : bookings){
                res[p[0]-1] += p[2];
                res[p[1]]   -= p[2];
            }
            for(int i=1; i<n; ++i)res[i] += res[i-1];
            res.pop_back();
            return res;
        }
//870. 优势洗牌
        std::vector<int> advantageCount(std::vector<int> &A, std::vector<int> &B){
            std::sort(begin(A), end(A));
            int len = A.size();
            std::vector<int> res(len,-1), vi(len);
            for(int i=len-1; i>=0; --i){
                int index = 0;
                while(1){
                    index = std::upper_bound(begin(A)+index, end(A), B[i]) - begin(A);
                    if(index == len)break;
                    if(vi[index]){
                        ++index;
                        continue;
                    }
                    vi[index] = 1;
                    res[i] = A[index];
                    break;
                }
            }
            int j = 0;
            for(int i=0; i<len; ++i){
                if(res[i] == -1){
                    while(vi[j++]);
                    res[i] = A[j-1];
                }
            }
            return res;
        }
//495. 提莫攻击
        int findPoisonedDuriation(std::vector<int> &timeSeries, int duration){
            int res = 0, t = -1, be = -1;
            for(auto &x : timeSeries){
                if(be==-1||t < x)res += t - be, be = x;
                t = x + duration;
            }
            return res + t - be;
        }
//891. 子序列宽度之和
        int sumSubseqWidths(std::vector<int> &A){
            using ll = long long;
            ll MOD = 1e9 + 7, res = 0, len = A.size();
            std::sort(begin(A), end(A));
            std::vector<ll> _pow(len+1);
            _pow[0] = 1;
            for(int i=1; i<=len; ++i)_pow[i] = (_pow[i-1] << 1) % MOD;
            for(int i=0; i<len; ++i){
                int l = i, r = len - i - 1;
                res = (res + A[i]*(_pow[l] - _pow[r])) % MOD;
            }
            return res % MOD;
        }
//918. 环形子数组的最大和
        int maxSubarraySumCircular(std::vector<int> &A){
            int len = A.size();
            if(!len)return 0;
            if(len==1)return A[0];
            int max_  = A[0], min_ = A[1], sums = A[0],
                max_v = A[0], min_v = A[1];
            for(int i=1; i<len; ++i){
                max_v = A[i] + std::max(0, max_v);
                max_ = std::max(max_, max_v);
                sums += A[i];
            }
            for(int i=2; i<len-1; ++i){
                min_v = A[i] + std::min(0, min_v);
                min_  = std::min(min_, min_v);
            }
            return std::max(max_, sums - min_);
        }
//1202. 交换字符串中的元素
        std::string smallestStringWithSwaps(std::string s, std::vector<std::vector<int>> &pairs){
            int len = s.size();
            std::vector<int> _f(len);
            std::iota(begin(_f), end(_f), 0);
            std::function<int(int)> _find = [&](int i){
                return _f[i]==i ? i : _f[i] = _find(_f[i]); };
            std::function<void(int, int)> _union = [&](int a, int b){
                _f[_find(a)] = _f[_find(b)]; };
            for(auto &p : pairs)_union(p[0], p[1]);
            std::unordered_map<int, std::vector<int>> mp;
            for(int i=0; i<len; ++i)mp[_find(i)].push_back(i);
            std::string res(len, '?'), temp;
            for(auto &&[p, v] : mp){
                temp = "";
                for(auto &i : v)temp += s[i];
                std::sort(begin(temp), end(temp));
                auto it = temp.begin();
                for(auto &index : v)res[index] = *it++;
            }
            return res;
        }
//1014. 最佳观光组合
        int maxScoreSightseeingPair(std::vector<int> &A){
            //std::priority_queue<int> q;
            int res = INT_MIN, len = A.size(), pre = 0;
            for(int i=0; i<len; ++i){
                res = std::max(res, pre + A[i] - i);
                pre = std::max(pre, i + A[i]);
                //if(q.size())res = std::max(res, q.top() - i + A[i]);
                //q.push(A[i] + i);
            }
            return res;
        }
//782. 变为棋盘
        int movesToChessboard(std::vector<std::vector<int>> &board){
            int n = board.size(), k1, k2;
            std::map<int, int> mp;
            for(auto &v : board){
                int num = 0;
                for(auto &x : v)num = (num<<1) | x;
                ++mp[num];
            }
            std::function<int(void)> _calc_cnt = [&](){
                if(mp.size() != 2)return -1;
                auto it = mp.begin();
                auto &&[k1, n1] = *it;
                auto &&[k2, n2] = *++it;
                if(!(n1==n/2 && n2==(n+1)/2)
                        && !(n2==n/2 && n1==(n+1)/2))return -1;
                int mod = (1<<n) - 1;
                if((k1 ^ k2) !=  mod)return -1;
                int cnt1 = __builtin_popcount(mod & k1);
                int ans  = INT_MAX;
                if(!(n&1) || cnt1*2 < n){
                    ans = std::min(ans, __builtin_popcount(k1 ^ 0xAAAAAAAA & mod)>>1);
                }
                if(!(n&1) || cnt1*2 > n){
                    ans = std::min(ans, __builtin_popcount(k1 ^ 0x55555555 & mod)>>1);
                }
                return ans;
            };
            if((k1=_calc_cnt()) == -1)return -1;
            mp = {};
            for(int j=0; j<n; ++j){
                int num = 0;
                for(int i=0; i<n; ++i)num = (num<<1) | board[i][j];
                ++mp[num];
            }
            if((k2=_calc_cnt()) == -1)return -1;
            return k1 + k2;
        }

//1338. 数组大小减半
        int minSerSize(std::vector<int> &arr){
            std::unordered_map<int, int> mp;
            for(auto &x : arr)++mp[x];
            int len = arr.size();
            std::vector<std::pair<int, int>> temp(begin(mp), end(mp));
            std::sort(begin(temp), end(temp), [&](auto &a, auto &b){
                    return a.second > b.second; });
            int res = 0, cnt = 0;
            for(auto &&[k, n] : temp){
                if((cnt += n) >= (len>>1))return ++res;
                ++res;
            }
            return res;
        }
//775. 全局倒置与局部倒置
        bool isIdealPermutation(std::vector<int> &A){
            int min_ = INT_MAX;
            for(int i=A.size()-1; i>=2; --i){
                min_ = std::min(min_, A[i]);
                if(A[i-2] > min_)return false;
            }
            return true;
        }
//792. 匹配子序列的单词数
        int numMatchingSubseq(std::string S, std::vector<std::string> &words){
            std::vector<std::vector<std::pair<std::string, int>>> buk(26);
            for(auto &s : words)buk[s[0]-'a'].emplace_back(s, 0);
            int res = 0;
            for(auto &c : S){
                auto wds   = buk[c-'a'];
                buk[c-'a'] = {};
                for(auto &&[str, index] : wds){
                    if(index==str.size()-1){
                        ++res;
                    }else{
                        buk[str[++index]-'a'].emplace_back(str, index);
                    }
                }
            }
            return res;
        }
        int numMatchingSubseq_fuck(std::string S, std::vector<std::string> &words){
            int res = 0, len = S.size();
            std::function<bool(std::string &)> _is_sub = [&](std::string &s){
                int i = 0, j = 0, len1 = s.size();
                while(i<len1 && j<len){
                    if(s[i] == S[j])++i;
                    ++j;
                }
                return i==len1;
            };
            for(auto &s : words)res += _is_sub(s);
            return res;
        }
//1386. 安排电影院座位
        int maxNumberOfFalilies(int n, std::vector<std::vector<int>> &reservedSeats){
            const int left  = 0b11110000;
            const int mid   = 0b00001111;
            const int right = 0b11000011;
            std::unordered_map<int, int> mp;
            for(auto &p : reservedSeats){
                if(p[1]>1 && p[1]<10){
                    mp[p[0]] |= (1<<(p[1]-2));
                }
            }
            int res = (n - mp.size())<<1;
            for(auto &&[k, v] : mp){
                res += ((left|v)==left || (mid|v)==mid || (right|v)==right);
            }
            return res;
        }
//31. 下一个排列
        void nextPermutation_11_14(std::vector<int> &nums){
            int i = nums.size() - 2;
            while(i>=0 && nums[i] >= nums[i+1])--i;
            if(i != -1){
                int r = nums.size() - 1;
                while(r>i && nums[i] >= nums[r])--r;
                std::swap(nums[r], nums[i]);
            }
            std::reverse(begin(nums)+i+1, end(nums));
        }
        void prevPermutation(std::vector<int> &nums){
            int i = nums.size() - 2;
            while(i>=0 && nums[i] <= nums[i+1])--i;
            if(i != -1){
                int r = i + 1;
                while(r>i && nums[i] <= nums[r])--r;
                std::swap(nums[i], nums[r]);
            }
            std::reverse(begin(nums) + i + 1, end(nums));
        }
        void nextPermutation(std::vector<int> &nums){
            //std::next_permutation(begin(nums), end(nums));
            int i = nums.size() - 2;
            while(i>=0 && nums[i+1] <= nums[i])--i;
            if(i==-1){
                reverse(begin(nums), end(nums));
            }else{
                int r = nums.size() - 1;
                while(r>i && nums[r] <= nums[i])--r;
                std::swap(nums[i], nums[r]);
                reverse(begin(nums)+i+1, end(nums));
            }
        }
//1031. 两个非重叠子数组的最大和
        int maxSumTwoNooverlap(std::vector<int> &A, int L, int M){
            std::vector<int> sums(A);
            int len = A.size(), res = INT_MIN;
            for(int i=1; i<len; ++i)sums[i] += sums[i-1];
            int l = 0, r = L - 1;
            std::function<int(int, int)> _find_max_M = [&](int il, int ir){
                int ans = INT_MIN;
                int ll = 0, rr = M - 1;
                while(rr < il){
                    ans = std::max(ans, sums[rr] - (ll?sums[ll-1]:0));
                    ++rr, ++ll;
                }
                ll = ir + 1, rr = ir + M;
                while(rr < len){
                    ans = std::max(ans, sums[rr] - sums[ll-1]);
                    ++rr, ++ll;
                }
                return ans;
            };
            while(r < len){
                res = std::max(res, sums[r]-(l?sums[l-1]:0) + _find_max_M(l, r));
                ++l, ++r;
            }
            return res;
        }
//54. 螺旋矩阵
        std::vector<int> spiralOrder(std::vector<std::vector<int>> &matrix){
            if(!matrix.size())return {};
            int m = matrix.size(), n = matrix[0].size();
            std::vector<int> res;
            int i = 0, j = 0, l = 0, r = n, d = m, u = 0;
            while(res.size() < n*m){
                while(res.size() < n*m && j<r)res.push_back(matrix[i][j++]);
                ++u, --j, ++i;
                while(res.size() < n*m && i<d)res.push_back(matrix[i++][j]);
                --r, --i, --j;
                while(res.size() < n*m && j>=l)res.push_back(matrix[i][j--]);
                --d, ++j, --i;
                while(res.size() < n*m && i>=u)res.push_back(matrix[i--][j]);
                ++l, ++i, ++j;
            }
            return res;
        }
//189. 旋转数组
        void retate(std::vector<int> &nums, int k){
            int len = nums.size(), mid = len - k%len - 1;
            int l = 0, r = mid;
            while(l < r)std::swap(nums[l++], nums[r--]);
            l = mid + 1, r = len - 1;
            while(l < r)std::swap(nums[l++], nums[r--]);
            l = 0, r = len - 1;
            while(l < r)std::swap(nums[l++], nums[r--]);
        }

//926. 将字符串翻转到单调递增
        int minFlipsMonoIncr(std::string S){
            int len = S.size();
            int f = 0, g = 0, nf = 0, ng = 0;
            for(int i=0; i<len; ++i){
                nf = f + (S[i] == '1');
                ng = std::min(g, f) + (S[i]=='0');
                f = nf, g = ng;
            }
            return std::min(f, g);
        }
//73. 矩阵置零
        void setzzzZeroes(std::vector<std::vector<int>> &matrix){
            int m = matrix.size(), n = matrix[0].size();
            int flag = 0;
            for(int i=0; i<m; ++i){
                if(!matrix[i][0])flag = 1;
                for(int j=1; j<n; ++j){
                    if(!matrix[i][j])matrix[i][0] = matrix[0][j] = 0;
                }
            }
            for(int i=m-1; i>=0; --i){
                for(int j=n-1; j>=1; --j){
                    if(!matrix[i][0] || !matrix[0][j])matrix[i][j] = 0;
                }
                if(flag)matrix[i][0] = 0;
            }
        }
//面试题 16.10. 生存人数
        int maxAliveYear(std::vector<int> &birth, std::vector<int> &death){
            std::vector<int> n(103);
            int len = birth.size(), ans = 0;
            for(int i=0; i<len; ++i){
                ++n[birth[i] - 1900];
                --n[death[i] - 1900 + 1];
            }
            for(int i=1; i<101; ++i){
                ans = std::max(ans, n[i] += n[i-1]);
            }
            for(int i=0; i<101; ++i){
                if(ans == n[i])return 1900+i;
            }
            return -1;
        }
//835. 图像重叠
        int largestDverlap(std::vector<std::vector<int>> &img1, std::vector<std::vector<int>> &img2){
            int n = img1.size();
            std::vector<int> flat_1, flat_2;
            for(int i=0; i<n; ++i){
                for(int j=0; j<n; ++j){
                    if(img1[i][j])flat_1.push_back((i<<6) + j);
                    if(img2[i][j])flat_2.push_back((i<<6) + j);
                }
            }
            int res = 0;
            std::unordered_map<int, int> mp;
            for(auto &a : flat_1){
                for(auto &b : flat_2){
                    res = std::max(res, ++mp[a - b]);
                }
            }
            return res;
        }
//1330. 翻转子数组得到最大的数组值
        int maxValueAfterReverse(std::vector<int> &nums){
        }
//581. 最短无序连续子数组
        int findUnsortedSubarray(std::vector<int> &nums){
            auto temp = nums;
            std::sort(begin(nums), end(nums));
            int l = 0, len = nums.size(), r = len - 1;
            while(l < len && temp[l] == nums[l])++l;
            if(l==len)return 0;
            while(r>=0 && temp[r]==nums[r])--r;
            return r - l + 1;
        }
//1053. 交换一次的先前排列
        std::vector<int> prevPremopt1(std::vector<int> &A){
            int len = A.size(), max_ = -1, sw = -1;
            if(std::is_sorted(begin(A), end(A)))return A;
            for(int i=len-1; i>=0; --i){
                for(int j=i+1; j<len; ++j){
                    if(A[i] > A[j] && max_ < A[j]){
                        max_ = A[j];
                        sw = j;
                    }
                }
                if(sw != -1){
                    std::swap(A[sw], A[i]);
                    return A;
                }
            }
            return A;
        }
//945. 使数组唯一的最小增量
        int minIncrementForUnique(std::vector<int> &A){
            std::sort(begin(A), end(A));
            int res = 0, len = A.size();
            for(int i=1; i<len; ++i){
                if(A[i-1] >= A[i]){
                    res += A[i-1] - A[i] + 1;
                    A[i] = A[i-1] + 1;
                }
            }
            return res;
            //std::vector<int> mp(80000);
            //for(auto &x : A)++mp[x];
            //int res = 0, need = 0;
            //for(int i=0; i<80000; ++i){
                //int v = mp[i];
                //if(v > 1){
                    //need += v - 1;
                    //res  -= i * (v - 1);
                //}else if(need>0 && !v){
                    //--need;
                    //res += i;
                //}
            //}
            return res;
        }
        int minIncrementForUnique_fuck(std::vector<int> &A){
            std::map<int, int> mp;
            for(auto &x : A)++mp[x];
            int res = 0;
            for(auto  [k, v] : mp){
                int r = k;
                while(v-- > 1){
                    while(!mp.insert({r++, 1}).second);
                    res += r - k - 1;
                }
            }
            return res;
        }
//1442. 形成两个异或相等数组的三元组数目
        int countTriplets(std::vector<int> &arr){
            std::unordered_map<int, std::vector<int>> mp;
            mp[0].push_back(-1);
            int res = 0, len = arr.size(), sum = 0;
            for(int i=0; i<len; ++i){
                sum ^= arr[i];
                for(auto &x : mp[sum])res += (i-x-1);
                mp[sum].push_back(i);
            }
            return res;
        }
//849. 到最近的人的最大距离
        int maxDistToClosest(std::vector<int> &seats){
            int ans = 0, res = 0, len = seats.size(), l = 0;
            for(int i=0; i<len; ){
                while(i<len && seats[i++]);
                l = i;
                while(i<len && !seats[i++]);
                ans = std::max(ans, i-l);
            }
            l = 0;
            while(l<len && !seats[l++]);
            res = std::max(l-1, (ans+(ans&1))>>1);
            l = len - 1;
            while(l>=0 && !seats[l--]);
            res = std::max(len-l-2, res);
            return res;
        }
//840. 矩阵中的幻方
        int numMagicSquaresInside(std::vector<std::vector<int>> &grid){
            int m = grid.size(), n = grid[0].size();
            if(m<3 || n<3)return- 0;
            std::function<bool(int, int)> _is_ok = [&](int x, int y){
                std::vector<int> mp(10);
                for(int i=x-2; i<=x; ++i){
                    int sum = 0;
                    for(int j=y-2; j<=y; ++j){
                        sum += grid[i][j];
                        if(grid[i][j]>9)return false;
                        if(++mp[grid[i][j]] > 1)return false;
                    }
                    if(sum != 15)return false;
                }
                for(int j=y-2; j<=y; ++j){
                    int sum = 0;
                    for(int i=x-2; i<=x; ++i){
                        sum += grid[i][j];
                    }
                    if(sum != 15)return false;
                }
                int t1 = grid[x][y] + grid[x-1][y-1] + grid[x-2][y-2];
                int t2 = grid[x][y-2] + grid[x-1][y-1] + grid[x-2][y];
                return t1==15 && t1==t2;
            };
            int res = 0;
            for(int i=2; i<m; ++i){
                for(int j=2; j<n; ++j){
                    res += _is_ok(i, j);
                }
            }
            return res;
        }
//1267. 统计参与通信的服务器
        int countServers(std::vector<std::vector<int>> &grid){
            int m = grid.size(), n = grid[0].size();
            int res = 0;
            for(int i=0; i<m; ++i){
                int ans = 0;
                for(int j=0; j<n; ++j){
                    ans += grid[i][j];
                }
                if(ans > 1){
                    res += ans;
                    for(auto &x : grid[i])if(x)x = 2;
                }
            }
            for(int j=0; j<n; ++j){
                int one = 0, ans = 0;
                for(int i=0; i<m; ++i){
                    ans += grid[i][j] == 1;
                    one += grid[i][j] > 0;
                }
                if(one > 1)res += ans;
            }
            return res;
        }
//228. 汇总区间
        std::vector<std::string> summaryRanges(std::vector<int> & nums){
            if(!nums.size())return {};
            if(nums.size() == 1)return {std::to_string(nums[0])};
            std::vector<std::string> res;
            std::vector<long long> temp(begin(nums), end(nums));
            std::sort(begin(temp), end(temp));
            temp.push_back(INT_MIN);
            int l = 0, len = temp.size();
            for(int i=1; i<len; ++i){
                if(temp[i]-1 != temp[i-1]){
                    std::string ans = std::to_string(temp[l])+(l==i-1 ? "" : "->" + std::to_string(temp[i-1]));
                    res.emplace_back(ans);
                    l = i;
                }
            }
            return res;
        }
//1343. 大小为 K 且平均值大于等于阈值的子数组数目
        int numOfSubarrays(::std::vector<int>& arr, int k, int t) {
            int res = 0;
            int sub = 0;
            int r   = 0;
            int size = arr.size();
            while(r < size){
                sub += arr[r] - t;
                if(r>=k)sub -= arr[r-k] - t;
                if(r>=k-1 && sub>=0)++res;
                ++r;
            }
            return res;
        }
//设计一个算法，判断玩家是否赢了井字游戏。输入是一个 N x N 的数组棋盘，由字符" "，"X"和"O"组成，其中字符" "代表一个空位。
//以下是井字游戏的规则：
//玩家轮流将字符放入空位（" "）中。
//第一个玩家总是放字符"O"，且第二个玩家总是放字符"X"。
//"X"和"O"只允许放置在空位中，不允许对已放有字符的位置进行填充。
//当有N个相同（且非空）的字符填充任何行、列或对角线时，游戏结束，对应该字符的玩家获胜。
//当所有位置非空时，也算为游戏结束。
//如果游戏结束，玩家不允许再放置字符。
//如果游戏存在获胜者，就返回该游戏的获胜者使用的字符（"X"或"O"）；如果游戏以平局结束，则返回 "Draw"；如果仍会有行动（游戏未结束），则返回 "Pending"。

    ::std::string tictactoe(::std::vector<::std::string>& board) {
        int size      = board.size();
        int null_flag = 0;
        ::std::string X(size,'X');
        ::std::string O(size,'O');
        for(int i=0; i<size; ++i){
            if(X == board[i])return "X";
            if(O == board[i])return "O";
        }
        ::std::string v1(""),v2("");
        int i=0,j=0,j1=size-1;
        while(i<size){
            v1 += board[i][j++];
            v2 += board[i++][j1--];
        }
        if(v1==X || v2==X)return "X";
        if(v1==O || v2==O)return "O";
        j = 0;
        while(j<size){
            ::std::string tmp("");
            for(int i=0; i<size; ++i){
                if(board[i][j] == ' ')null_flag = 1;
                tmp += board[i][j];
            }
            if(X == tmp)return "X";
            if(O == tmp)return "O";
            ++j;
        }
        return null_flag?"Pending":"Draw";
    }
//给你一个整数数组 nums，每次 操作 会从中选择一个元素并 将该元素的值减少 1。
//如果符合下列情况之一，则数组 A 就是 锯齿数组：
//每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
//或者，每个奇数索引对应的元素都大于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
//返回将数组 nums 转换为锯齿数组所需的最小操作次数
    int movesToMakeZigzag(::std::vector<int>& nums) {
        int size = nums.size();
        int res1 = 0;
        int res2 = 0;
        for(int i=0; i<size; ++i){
            int l = i?nums[i-1]:INT_MAX;
            int r = i==size-1?INT_MAX:nums[i+1];
            if(i&1){
                res1 += ::std::max(0, nums[i] - ::std::min(l,r) + 1);
            }else{
                res2 += ::std::max(0, nums[i] - ::std::min(l,r) + 1);
            }
        }
        return ::std::min(res1, res2);
    }
//学校在拍年度纪念照时，一般要求学生按照 非递减 的高度顺序排列。
//请你返回能让所有学生以 非递减 高度排列的最小必要移动人数。
//注意，当一组学生被选中时，他们之间可以以任何可能的方式重新排序，而未被选中的学生应该保持不动。
    int heightChecker(::std::vector<int>& h) {
        ::std::vector<int> tmp(h);
        ::std::sort(tmp.begin(), tmp.end());
        int res  = 0;
        int size = h.size();
        for(int i=0; i<size; ++i){
            if(tmp[i] != h[i])++res;
        }
        return res;
    }
//给你数字 k ，请你返回和为 k 的斐波那契数字的最少数目，其中，每个斐波那契数字都可以被使用多次。
//斐波那契数字定义为：
//F1 = 1
//F2 = 1
//Fn = Fn-1 + Fn-2 ， 其中 n > 2 。
//数据保证对于给定的 k ，一定能找到可行解。
    int findMinFibonacciNumbers(int k){
        ::std::vector<int> dp(2,1);
        int i = 0;
        int j = 1;
        while(1){
            int t = dp[i++] + dp[j++];
            dp.push_back(t);
            if(t ==k)return 1;
            if(t > k)break;
        }
        int res = 0;
        j       = dp.size();
        while(k && j){
            if(dp[--j]<=k)k -= dp[j],++res;
        }
        return res;
    }
//给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用。
//你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
//返回获得利润的最大值。
//注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
    int maxPoit(::std::vector<int>& prices, int fee){
        int n = prices.size();
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for (int i = 0; i < n; i++) {
            int temp = dp_i_0;
            dp_i_0 = ::std::max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = ::std::max(dp_i_1, temp - prices[i] - fee);
        }
        return dp_i_0;
    }
//在老式手机上，用户通过数字键盘输入，手机将提供与这些数字相匹配的单词列表。每个数字映射到0至4个字母。给定一个数字序列，实现一个算法来返回匹配单词的列表。你会得到一张含有有效单词的列表。映射如下图所示：
    ::std::unordered_map<char,::std::pair<int,int>> hs = {
        {'2', ::std::make_pair('a','c')},
        {'3', ::std::make_pair('d','f')},
        {'4', ::std::make_pair('g','i')},
        {'5', ::std::make_pair('j','l')},
        {'6', ::std::make_pair('m','o')},
        {'7', ::std::make_pair('p','s')},
        {'8', ::std::make_pair('t','v')},
        {'9', ::std::make_pair('w','z')}
    };
    ::std::vector<::std::string> getValid9Words(::std::string sum, ::std::vector<::std::string>& words){
        ::std::vector<::std::string> res;
        int size = sum.length();
        int i    = 0;
        for(::std::string &s : words){
            if(size != s.length())continue;
            for(i=0;i<size; ++i){
                if(hs[sum[i]].first<=s[i]&&hs[sum[i]].second>=s[i])continue;
                break;
            }
            if(i==size)res.push_back(s);
        }
        return res;
    }
//绘制直线。有个单色屏幕存储在一个一维数组中，使得32个连续像素可以存放在一个 int 里。屏幕宽度为w，且w可被32整除（即一个 int 不会分布在两行上），屏幕高度可由数组长度及屏幕宽度推算得出。请实现一个函数，绘制从点(x1, y)到点(x2, y)的水平线。
//给出数组的长度 length，宽度 w（以比特为单位）、直线开始位置 x1（比特为单位）、直线结束位置 x2（比特为单位）、直线所在行数 y。返回绘制过后的数组。
    ::std::vector<int> drawLine(int length, int w, int x1, int x2, int y){
        ::std::vector<int>res(length,0);
        for(int i=x1; i<=x2; ++i){
            res[i/32 + y*w/32] |= (1<<(31-i%32));
        }
        return res;
    }

//给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组，并返回其长度。如果不存在符合条件的连续子数组，返回 0。
//    O(n)
    int minSubArrayLen(int s, ::std::vector<int>& nums){
        int r    = 0;
        int l    = 0;
        int size = nums.size();
        int sum  = 0;
        int res  = size+1;
        while(r<size){
            if((sum += nums[r++])<s)continue;
            while(sum>=s && l<=r){
                sum -= nums[l++];
            }
            res = ::std::min(res, r-l+1);
        }
        return res==size+1?0:res;
    }
//    O(log(n))  ???????????
    int minSubArrayLen1(int s,::std::vector<int>& nums){
        int size = nums.size();
        int res = size + 1;
        ::std::vector<int>sums(nums);
        for(int i=1; i<size; ++i)sums[i] += sums[i-1];
        for(int i=0; i<size; ++i){
            int  found = s+sums[i];
            auto bound = ::std::lower_bound(sums.begin(), sums.end(), found);
            if(bound != sums.end()){
                res = ::std::min(res, static_cast<int>(bound-(sums.begin()+i)));
            }
        }
        return res==size+1?0:res;
    }

//给你一份『词汇表』（字符串数组） words 和一张『字母表』（字符串） chars。
//假如你可以用 chars 中的『字母』（字符）拼写出 words 中的某个『单词』（字符串），那么我们就认为你掌握了这个单词。
//注意：每次拼写（指拼写词汇表中的一个单词）时，chars 中的每个字母都只能用一次。
//返回词汇表 words 中你掌握的所有单词的 长度之和。
    int countCharacters(::std::vector<::std::string>& words, ::std::string chars) {
        ::std::vector<int>c(26,0);
        int size = chars.length();
        int res  = 0;
        for(int i=0; i<size; ++i)++c[chars[i]-'a'];
        for(::std::string &w : words){
            ::std::vector<int> tmp(c);
            int i = 0;
            for(; i<w.length(); ++i){
                if(--tmp[w[i]-'a']<0)break;
            }
            if(i == w.length())res += i;
        }
        return res;
    }
//给定一个非负整数，你至多可以交换一次数字中的任意两位。返回你能得到的最大值
    int maximumSwap(int num){
        ::std::string s = ::std::to_string(num);
        int i           = 1;
        int size        = s.length();
        while(i<size && s[i]<=s[i-1])++i;
        if(i==size)return num;
        int f = s[i];
        int j = i++;
        for(; i<size; ++i){
            if(f<=s[i]){
                f = s[i];
                j = i;
            }
        }
        i = 0;
        for(; i<size; ++i){
            if(s[i]<f)break;
        }
        ::std::swap(s[j], s[i]);
        return atoi(s.c_str());
    }
//给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
    int subarraySum(::std::vector<int>& nums, int k){
        ::std::unordered_map<int,int> hp;
        hp[0]   = 1;
        int res = 0;
        int sum = 0;
        for(auto &n : nums){
            res += hp[(sum += n)-k];
            ++hp[sum];
        }
        for(auto &n : hp){
            ::std::cout<<n.first<<"--"<<n.second<<::std::endl;
        }
        return res;
    }
    int test(){
        ::std::unordered_map<int,int>hp;
        for(int i=0; i<20; ++i){
            ::std::cout<<hp[i]<<::std::endl;
        }
        return 0;
    }
//给定一个整数数组，返回所有数对之间的第 k 个最小距离。一对 (A, B) 的距离被定义为 A 和 B 之间的绝对差值。
    int smallestDistancePair(::std::vector<int>& nums, int k) {
        ::std::priority_queue<int> hp;
        int size = nums.size();
        for(int i=0; i<size; ++i){
            for(int j=i+1; j<size; ++j){
                int tmp = abs(nums[i]-nums[j]);
                if(hp.size()==k){
                    if(hp.top()>tmp){
                        hp.pop();
                        hp.push(tmp);
                    }
                }else{
                    hp.push(tmp);
                }
            }
        }
        return hp.top();
    }
    // 2--search
    int smallestDistancePair1(::std::vector<int>& nums, int k) {
        ::std::sort(nums.begin(), nums.end());
        int size  = nums.size();
        int left  = 0;
        int right = nums[size-1] - nums[0];
        while(left < right){
            int mid = left + ((right-left)>>1);
            if(calc(nums,mid)>=k){
                right = mid;
            }else{
                left  = mid + 1;
            }
        }
        return left;
    }
    int calc(::std::vector<int>& nums, int mid){
        int l=0,r=0;
        int size = nums.size();
        int res  = 0;
        while(r<size){
            while(nums[r]-nums[l] > mid)++l;
            res += r - l;
            ++r;
        }
        return res;
    }

//给你一个数组 arr ，请你将每个元素用它右边最大的元素替换，如果是最后一个元素，用 -1 替换。
//完成所有替换操作后，请你返回这个数组。
    ::std::vector<int> replaseElements(::std::vector<int>& nums){
        int size = nums.size();
        if(size==0)return nums;
        int m    = nums[size-1];
        int t    = INT_MIN;
        nums[size-1] = -1;
        for(int i=size-2; i>=0; --i){
            t = nums[i];
            nums[i] = m;
            m = ::std::max(m, t);
        }
        return nums;
    }

//给定一个放有字符和数字的数组，找到最长的子数组，且包含的字符和数字的个数相同。
//返回该子数组，若存在多个最长子数组，返回左端点最小的。若不存在这样的数组，返回一个空数组。
    ::std::vector<::std::string> findLongestSubarray(::std::vector<::std::string>& array){
        ::std::unordered_map<int,int> hp;
        int s = 0;
        int e = 0;
        int n = 0;
        int size = array.size();
        for(int i=0; i<size; ++i){
            if(::std::isdigit(array[i][0])){
                ++n;
            }else{
                --n;
            }
            if(n==0){
                s = 0;
                e = i;
            }else if(hp.count(n)==0){
                hp[n] = i;
            }else if(i-hp[n]-1 > e-s){
                s = hp[n] + 1;
                e = i;
            }
        }
        if(s==e)return {};
        return ::std::vector<::std::string>(array.begin()+s, array.begin()+e);
    }
//给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
//函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。
    ::std::vector<int> twoSum(::std::vector<int>& nums, int target){
        int size = nums.size();
        int l = 0;
        int r = size - 1;
        while(l<r){
            int sum  = nums[l] + nums[r];
            if(sum < target){
                ++l;
            }else if(sum > target){
                --r;
            }else{
                return {++l,++r};
            }
        }
        return {};
    }
//给定一个数组，包含从 1 到 N 所有的整数，但其中缺了两个数字。你能在 O(N) 时间内只用 O(1) 的空间找到它们吗？
//以任意顺序返回这两个数字均可。
    ::std::vector<int> missTwo(::std::vector<int>& nums){
        int size = nums.size();
        int x    = 0;
        int p    = 0;
        for(int i=0; i<size+2; ++i)x ^= (i+1);
        for(int i=0; i<size; ++i)x ^= nums[i];
        int f = x & ~x+1;
        int t = 0;
        for(int i=0; i<size; ++i){
            if(nums[i]&f)t ^= nums[i];
        }
        for(int i=1; i<=size+2; ++i){
            if(i&f)t ^= i;
        }
        return {t, x^t};
    }
};
int main(int argc,const char *argv[]){
    Solution te;
    ::std::vector<int>nums = {2,3,1,2,-2,-3,-4,4,5,1,2,3,4,5,6};
    te.subarraySum(nums, 3);
    //::std::cout<<te.findMinFibonacciNumbers(19)<<::std::endl;
    return 0;
}
